#include "channel.h"
#include "QDataStream"
#include <iostream>

Channel::Channel(ClientInfo otherClient, quintptr descriptor, bool genKey, QObject *parent) : QObject(parent),
    otherClientName(otherName), encrypted(false), otherSideAuthorized(false), generateSymKey(genKey)
{
    qDebug() << "initialize server channel";
    initialize();
    socket->setSocketDescriptor(descriptor);
    otherClientInfo = otherClient;
    otherRsa.setPartnerPublicKey(otherClient.publicKey);
}

Channel::Channel(ClientInfo otherClient, bool genKey, QObject *parent) : QObject(parent), encrypted(false), otherSideAuthorized(false),
    generateSymKey(genKey)
{
    initialize();
    otherClientInfo = otherClient;
    otherRsa.setPartnerPublicKey(otherClient.publicKey);
    otherClientName = otherName;
}


QString Channel::getOtherClientName()
{
    return otherClientName;
}

QByteArray Channel::encryptMessage(QString text)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "send_message");
    jsonObject.insert("data", text);
    QJsonDocument jsonDoc(jsonObject);

    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);
}

QByteArray Channel::encryptSendAuthorizarionMessage(QString message)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "auth");
    jsonObject.insert("message", authorizationMessage);
    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return otherRsa.encryptMessage(array);

}

QByteArray Channel::encryptSendSymKey(QString key)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "set_key");
    jsonObject.insert("key", key);
    QJsonDocument jsonDoc(jsonObject);

    QByteArray array(jsonDoc.toBinaryData());
    return otherRsa.encryptMessage(array);

}

QJsonDocument Channel::decrypt(QByteArray array)
{
    return gcm.decryptAndAuthorizeFull(array);
}

void Channel::sendAuthorizationMessage()
{
    socket->write(encryptSendAuthorizarionMessage(authorizationMessage));
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}

void Channel::sendSymetricKey()
{
    socket->write(encryptSendSymKey(gcm.getKey()));
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
    emit onChannelConnected(otherClientInfo.name);
}




void Channel::readyRead()
{
    qDebug() << "ready read !!!";
   buffer.append(socket->readAll());
   if (buffer.fullMessageRead()){
       QByteArray data = buffer.getData();
        Parser parser;
       if (encrypted) {
           parser = Parser(gcm.decryptAndAuthorizeFull(data));
           if (! parser.verifyId(nextId)){
               // ids do not match so just discard this message
               return;
           }
           QString type = parser.get("type");
           if (type == "send_message"){
               QString text = parser.get("data");
               text.prepend(otherClientName + "> ");
               text.append("\r\n");
               qDebug() << "received text: " << text;
               emit onMessageReceived(text, otherClientName);
           }

       } else{
           parser = Parser(rsa.decryptMessage(data));
           QString type = parser.get("type");
           if (type == "auth"){
               if (otherSideAuthorized){
                   qDebug() << "received authorization message after authorization !!!";
                   return;
               }
               QString authMessage = parser.get("message");
               if (authMessage != authorizationMessage){
                   qDebug() << "authorization message differs from message received";
                   return;
               }
               otherSideAuthorized = true;
               if (generateSymKey){
                   sendSymetricKey();
               }
           }
           if (! otherSideAuthorized){
               qDebug() << "received message while not in authorized state !!" ;
               return;
           }
           if (type == "set_key"){
               if (generateSymKey){
                   qDebug() << "received sym key when this side generated the key";
                   return;
               }
               QString key = parser.get("key");
               bool res = gcm.setKey(key.toStdString().c_str());
               if (!res){
                   qDebug() << "could not set symetric key";
               }
               encrypted = true;
               connected = true;
               emit onChannelConnected(otherClientInfo.name);
               qDebug() << "symetric key was set";
           }
       }
   }
   buffer.reset();
}

void Channel::connectToHost(quintptr port)
{
    socket->connectToHost(otherClientInfo.clientAddress, port);
    if (!socket->waitForConnected()){
        qDebug() << "could not connect to socket";
        return;
    }
    sendAuthorizationMessage();
    //emit onChannelConnected(otherName);
    qDebug() << "channel connect to host: " << socket->isValid();
}

void processReceivedData(QByteArray& array){

}

void Channel::sendMessage(QString message)
{
    socket->write(encryptMessage(message));
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";

}

void Channel::sendFile(QByteArray data)
{

}

void Channel::initialize(){
    gcm.initialize();

    if (generateSymKey){
        gcm.generateGcmKey();
    }
    socket = new QTcpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

/*unsigned char* Channel::generateGcmKey()
{
    return gcm.generateGcmKey();
}*/

void Channel::setkey(unsigned char * newKey)
{
    gcm.setKey(newKey);

}
