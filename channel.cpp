#include "channel.h"
#include "QDataStream"

Channel::Channel(QString otherName, quintptr descriptor, QObject *parent) : QObject(parent), otherClientName(otherName)
{
    qDebug() << "initialize server channel";
    initialize();
    otherClientName = otherName;
    socket->setSocketDescriptor(descriptor);
    qDebug() << "before emit";
    //emit onChannelConnected(otherName);
    qDebug() << "after emit";
}

Channel::Channel(QString otherName, QObject *parent) : QObject(parent)
{
    initialize();
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

QJsonDocument Channel::decrypt(QByteArray array)
{
    return gcm.decryptAndAuthorizeFull(array);
}




void Channel::readyRead()
{
    qDebug() << "ready read !!!";
   buffer.append(socket->readAll());
   if (buffer.fullMessageRead()){
       QByteArray data = buffer.getData();
        Parser parser;
       if (encrypted){
           parser = Parser(gcm.decryptAndAuthorizeFull(data));
           if (! parser.verifyId(nextId)){
               // ids do not match so just discard this message
               return;
           }
           QString type = parser.get("type");
           if (type == "send_message"){
               QString text = parser.get("data");
               qDebug() << "received text: " << text;
               emit onMessageReceived(text, otherClientName);
           }

       }
   }
   buffer.reset();
}

void Channel::connectToHost(QString otherName, const QHostAddress &hostAddress, quintptr port)
{
    socket->connectToHost(hostAddress, port);
    if (!socket->waitForConnected()){
        qDebug() << "could not connect to socket";
    }
    emit onChannelConnected(otherName);
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
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    setkey(key);
    socket = new QTcpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

unsigned char* Channel::generateGcmKey()
{
    return gcm.generateGcmKey();
}

void Channel::setkey(unsigned char * newKey)
{
    gcm.setKey(newKey);

}
