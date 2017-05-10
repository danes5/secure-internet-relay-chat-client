#include "Connection.h"
#include "parser.h"

void Connection::processGetRequest()
{

}

Connection::Connection(quintptr descriptor, rsautils &rsa, QObject *parent) : QObject(parent), encrypted(false), registered(false),
    server(static_cast<Server*> (parent)), rsa(rsa)
{
    initialize();

    socket = new QSslSocket();
    socket->setSocketDescriptor(descriptor);
    socket->setProtocol(QSsl::TlsV1SslV3);

    QFile file_key("server.key");
    if (!file_key.open(QIODevice::ReadOnly)) {
        qDebug() << file_key.errorString();
        return;
    }
    file_key.close();

    QFile file_cert("server.csr");
    if (file_cert.open(QIODevice::ReadOnly)) {
        qDebug() << file_cert.errorString();
        return;
    }
    file_cert.close();

    socket->setPrivateKey("server.key");
    socket->setLocalCertificate("server.csr");
    socket->startServerEncryption();

    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslError(QList<QSslError>)));
    connect(socket, SIGNAL(encrypted()), this, SLOT(readyRead()));
    qDebug() << "connection initialized";

}

void Connection::initialize(){
    gcm.initialize();
}

/*unsigned char* Connection::generateGcmKey()
{
    return gcm.generateGcmKey();
}*/

void Connection::setkey(unsigned char * newKey)
{
    gcm.setKey(newKey);

}

void Connection::processRegistrationRequest(ClientInfo clInfo, bool result)
{
    qDebug() << "registration request:  " << clInfo.name;
    registered = result;
    clientInfo = clInfo;
    sendRegistrationReply(clInfo.name, result);
}

/*Connection::Connection(QObject *parent)
{
    //qDebug() << "created connection on:" << socketDescriptor();
    //qDebug() << isValid();
}*/

/*const ClientInfo &Connection::getClientInfo()
{
    return clientInfo;

}*/

bool Connection::isReady()
{
   return registered && encrypted;

}

Connection::~Connection()
{

}

QByteArray Connection::encryptAndTag(QJsonObject json)
{
    QJsonDocument jsonDoc(json);
    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);

}

QByteArray Connection::encryptGetRegisteredClientsReply()
{
    QJsonObject result;
    QJsonObject jsonClients = server->getRegisteredClientsInJson();
    result["data"] = jsonClients;
    result["type"] = "ret_cli";
    return encryptAndTag(result);

}

QByteArray Connection::encryptChannelRequest(QJsonObject data)
{
    return encryptAndTag(data);
}

QByteArray Connection::encryptChannelReply(QJsonObject data)
{
    return encryptAndTag(data);
}

QByteArray Connection::encryptSendClientInfo(QJsonObject data)
{
    QJsonObject result;
    result["type"] = "cli_info";
    result["info"] = data["info"];
    return encryptAndTag(result);
}

QByteArray Connection::encryptRegistrationReply(QString name, bool result)
{
    QJsonObject json;
    json["type"] = "reg_rep";
    json["name"] = name;
    json["result"] = result ? "acc" : "rej";
    return encryptAndTag(json);
}

void Connection::sendRegisteredClients()
{
    QByteArray array = encryptGetRegisteredClientsReply();
    socket->write(array);
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}

void Connection::sendRegistrationReply(QString name, bool result)
{
    qDebug() << "sending registration reply to name: " << name << "with result: " << result;
    QByteArray array = encryptRegistrationReply(name, result);
    socket->write(array);
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}

bool Connection::isRegistered()
{
    return registered;
}

QString Connection::getName()
{
    return clientInfo.name;
}

void Connection::sendChannelRequest(QJsonObject data){
    //qDebug() << "forwarding channel request from server";
    //qDebug() << "just checking client : " << data["client"];
    QByteArray array = encryptChannelRequest(data);
    socket->write(array);
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}

void Connection::sendChannelReply(QJsonObject data){
    QByteArray array = encryptChannelReply(data);
    socket->write(array);
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}





void Connection::connected()
{
    //write("ahoj", 4);


}

void Connection::disconnected()
{

}

void Connection::readyRead()
{
    qDebug() << "ready read !!!";
   buffer.append(socket->readAll());
   if (buffer.fullMessageRead()){
       QByteArray data = buffer.getData();
       buffer.reset();
        Parser parser;
       if (encrypted) {
           parser = Parser(gcm.decryptAndAuthorizeFull(data));
           if (! parser.verifyId(nextId)){
               // ids do not match so just discard this message
               return;
           }
           QString type = parser.get("type");
           if (type == "get_cli"){
                qDebug() << "get active clients request";
                sendRegisteredClients();
           } else
           if (type == "reg_req"){
               ClientInfo clInfo = parser.getClientInfo();
               emit onRegistrationRequest(clInfo);
               //qDebug() << "registration request received from client: " << name;
           } else
           if (type == "req_cre"){
               QJsonObject json = parser.getJson();
               QString destName = parser.get("client");

               QJsonObject clInfoObject;
               //clientInfo.name = clientName;
               clientInfo.write(clInfoObject);
               json.insert("info", clInfoObject);
               qDebug() << "received communication request to client: " << destName << " from client: " << clientInfo.name;
               emit onCreateChannelRequest(destName, json);

           } else
           if (type == "req_rep"){
               QJsonObject jsonObject;

               int id = parser.getId();
               QString name = parser.get("client");
               QString res = parser.get("result");
               jsonObject.insert("result", res);
               if (res == "acc"){
                   QJsonObject clientInf;
                   clientInfo.write(clientInf);
                   jsonObject.insert("info", clientInf);
                   jsonObject.insert("id", id);
               }
               jsonObject.insert("type", "req_rep");
               emit onCreateChannelReply(name, jsonObject);


               qDebug() << "received communication reply to client: " << name << " with result: " << res;
           } else
           if (type == "quit"){
               emit onQuit(this);
           }





       } else{
           qDebug() << "RSA read";
           parser = Parser(QJsonDocument::fromBinaryData( rsa.decryptMessage(data)));
           if (! parser.verifyId(nextId)){
               // ids do not match so just discard this message
               return;
           }
           QString type = parser.get("type");
           if (type == "set_key"){
               qDebug() << "set key !!!!!!!!!!!!!!!!!!!!!!!!!!";
               QString key = parser.get("key");

               setkey((unsigned char *)key.toLatin1().data());
               qDebug() << "key is: " << gcm.getKey();
               encrypted = true;
           }
       }
   }



}

void Connection::bytesWritten(qint64 bytes)
{

}

void Connection::stateChanged(QAbstractSocket::SocketState socketState)
{

}

void Connection::error(QAbstractSocket::SocketError socketError)
{

}

void Connection::sslError(QList<QSslError> errors) {
    qDebug() << "SLL error:\t" << errors;
}
