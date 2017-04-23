#include "serverconnection.h"
/*ServerConnection::ServerConnection(QObject* parent) : QObject(parent)
{
    socket = new QTcpSocket();
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    socket->connectToHost(QHostAddress::LocalHost, 5000);
    qDebug() << "constructor";
    //socket->write("akafuka", 7);
}*/

ServerConnection::ServerConnection(QObject *parent = nullptr) : QObject(parent)
{
    initialize();
    socket->connectToHost(QHostAddress::LocalHost, 5000);
    qDebug() << "constructor";
}

QByteArray ServerConnection::encryptRegistrationRequest(QString clientName)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "reg_req");
    jsonObject.insert("client", clientName);
    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);

}

QByteArray ServerConnection::encryptCreateChannelRequest(QString clientName)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "req_cre");
    jsonObject.insert("client", clientName);
    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);
}

QByteArray ServerConnection::encryptCreateChannelReply(bool reply, QString clientName)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "req_rep");
    jsonObject.insert("client", clientName);
    jsonObject.insert("result", reply ? "acc" : "rej");
    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);
}

QByteArray ServerConnection::encryptGetActiveClientsRequest()
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "get_cli");
    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);
}

QByteArray ServerConnection::encryptClientInfo()
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "cli_info");
    clientInfo.write(jsonObject);
    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);
}

void ServerConnection::socketStateChanged(QAbstractSocket::SocketState state)
{

}

void ServerConnection::socketError(QAbstractSocket::SocketError error)
{

}

void ServerConnection::initialize(){
    gcm.initialize();
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    setkey(key);

    socket = new QTcpSocket();
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

unsigned char* ServerConnection::generateGcmKey()
{
    return gcm.generateGcmKey();
}

void ServerConnection::setkey(unsigned char * newKey)
{
    gcm.setKey(newKey);

}

/*ServerConnection::~ServerConnection()
{

}*/

void ServerConnection::connected()
{
    qDebug() << "connected";
    //qDebug() << "sending registration request";
    //sendRegistrationRequest("name1");
    //sendGetActiveClientsRequest();
    //sendCreateChannelRequest("client123");
    //sendCreateChannelReply(true, "client456");

}

void ServerConnection::readyRead()
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
           if (type == "ret_cli"){
                qDebug() << "returned get clients";
           }else
           if (type == "req_cre"){
               QString client = parser.get("client");
               qDebug() << "received request for communication from: client: " << client;
           }else
           if (type == "req_rep"){
               QString client = parser.get("client");
               qDebug() << "received reply for communication from: client: " << client;
           }else
           if (type == "reg_rep"){
               QString result = parser.get("result");
               QString name = parser.get("name");
               qDebug() << "received reply for registration, result: " << result;
               emit onRegistrationReply(name, result);
           }

       }
    }

}

void ServerConnection::sendRegistrationRequest(QString clientName)
{
    qDebug() << "socket is valid: " << socket->isValid();
    QByteArray array = encryptRegistrationRequest(clientName);
    socket->write(array);
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
    qDebug() << "registration request sent, length: " << array.length() ;
}

void ServerConnection::sendCreateChannelRequest(QString clientName)
{
    socket->write(encryptCreateChannelRequest(clientName));
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}

void ServerConnection::sendCreateChannelReply(bool reply, QString clientName)
{
    socket->write(encryptCreateChannelReply(reply, clientName));
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}

void ServerConnection::sendGetActiveClientsRequest()
{
    socket->write(encryptGetActiveClientsRequest());
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}
