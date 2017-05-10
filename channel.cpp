#include "channel.h"
#include "QDataStream"
#include <iostream>

Channel::Channel(ClientInfo otherClient, bool genKey, rsautils& rsa, QObject *parent) : QObject(parent),
    otherClientInfo(otherClient), encrypted(false), otherSideAuthorized(false), generateSymKey(genKey), hasInfo(true), rsa(rsa)
{
    qDebug() << "initialize server channel";
    initialize();

    otherClientInfo = otherClient;
    otherRsa.setPartnerPublicKey(otherClient.publicKey);
}

Channel::Channel(QList<ClientInfo> *connections, QList<int> *ids, quintptr descriptor, bool genKey, rsautils &rsa, QObject *parent) :
    QObject(parent), encrypted(false), otherSideAuthorized(false),
    generateSymKey(genKey), hasInfo(false), connections(connections), ids(ids), rsa(rsa)
{

    initialize();
    socket->setSocketDescriptor(descriptor);
}


QString Channel::getOtherClientName()
{
    return otherClientInfo.name;
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
    qDebug() << "sending authorization message";
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
    //emit onChannelConnected(otherClientInfo.name);
}

void Channel::sendId(int id)
{
    qDebug() << "sending id: " << id;
    QJsonObject json;
    json["type"] = "set_id";
    json["id"] = id;
    QJsonDocument doc(json);
    //QByteArray data = doc.toBinaryData();
    quint64 len = doc.toBinaryData().length();
    qDebug() << "send id length : " << len;
    //data.prepend((char*)&len, sizeof(quint64));
    //QByteArray completeData;
    char cData [len + sizeof(quint64)];
    memcpy(cData, (char*)&len, sizeof(quint64));
    memcpy(cData + sizeof(quint64) ,doc.toBinaryData().data(), len);
    QByteArray completeData(cData, len + sizeof(quint64));
    socket->write(completeData);
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";


}





void Channel::readyRead()
{
    qDebug() << "channel ready read !!!";
    QByteArray b(socket->readAll()) ;
   buffer.append(b);
   if (buffer.fullMessageRead()) {
       //qDebug() << "message read full";
       QByteArray data = buffer.getData();
       buffer.reset();
        Parser parser;
        if (!hasInfo) {
            //qDebug() << "should receive id";
            parser = Parser(QJsonDocument::fromBinaryData(data));
            QString type = parser.get("type");
            if (type != "set_id"){
                qDebug() << "did not receive id";
                return;
            }


            int index = -1;
            int id = parser.getId();
            qDebug() << "received id: " << id;
            for (int i = 0; i < ids->length(); ++i ){
                if (ids->at(i) == id){
                    index = i;
                    break;
                }
            }
            if (index == -1){
                qDebug() << "received request from unknown client";
                return;
            }
            otherClientInfo = connections->at(index);
            connections->removeAt(index);
            ids->removeAt(index);
            qDebug() << "channel connected and recognized client: " << otherClientInfo.name;
            hasInfo = true;
            otherRsa.setPartnerPublicKey(otherClientInfo.publicKey);
            auto x = otherClientInfo.publicKey;
            sendAuthorizationMessage();
            //sendSymetricKey();
            //encrypted = true;
            //connected = true;
            //emit onChannelActive(otherClientInfo.name);
            return;

        }
       if (encrypted) {
           parser = Parser(gcm.decryptAndAuthorizeFull(data));
           if (! parser.verifyId(nextId)){
               // ids do not match so just discard this message
               return;
           }
           QString type = parser.get("type");
           if (type == "send_message"){
               QString text = parser.get("data");
               text.prepend(getOtherClientName() + "> ");
               text.append("\r\n");
               qDebug() << "received text: " << text;
               emit onMessageReceived(text, getOtherClientName());
           }

       } else{
           parser = Parser(QJsonDocument::fromBinaryData( rsa.decryptMessage(data)));
           QString type = parser.get("type");
           if (type == "auth") {
               if (otherSideAuthorized){
                   qDebug() << "received authorization message after authorization !!!";
                   return;
               }
               QString authMessage = parser.get("message");
               if (authMessage != authorizationMessage){
                   qDebug() << "authorization message differs from message received";
                   return;
               }
               qDebug() << "authorized!!!!!!!!!!!!!!!!!!";
               otherSideAuthorized = true;
               //if (generateSymKey){
                 //  sendSymetricKey();
               //}

               if (!generateSymKey){
                   sendAuthorizationMessage();
               }
               else {
                   sendSymetricKey();
                   encrypted = true;
                   connected = true;
                   emit onChannelActive(otherClientInfo.name);
               }
               return;
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
               qDebug() << "received string key: " << key;
               bool res = gcm.setKey((unsigned char *)key.toLatin1().data());
               if (!res){
                   qDebug() << "could not set symetric key";
               }
               qDebug() << "channel received key: " << gcm.getKey();
               encrypted = true;
               connected = true;
               emit onChannelActive(otherClientInfo.name);
               qDebug() << "symetric key was set";
               return;
           }
       }
   }
   qDebug() << "incomplete message, rest will be send in next packet, length: " << buffer.getLength();

}

void Channel::connectToHost(quintptr port)
{
    socket->connectToHost(otherClientInfo.clientAddress, port);
    if (!socket->waitForConnected()){
        qDebug() << "could not connect to socket";
        return;
    }
    //sendAuthorizationMessage();
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
    qDebug() << "channel generated key: " << gcm.getKey();
    int ret = otherRsa.initialize();
    if (ret != 0){
        qDebug() << "could not initialize other rsa:  " << ret;
    }
    socket = new QTcpSocket(this);
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
