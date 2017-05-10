#include "serverconnection.h"

ServerConnection::ServerConnection(ClientInfo &clInfo, rsautils& rsa, QObject *parent = nullptr) :
    QObject(parent), clientInfo(clInfo), encrypted(false), rsa(rsa)
{
    if (!initialize()){
        return;
    }


}

QByteArray ServerConnection::encryptRegistrationRequest(QString clientName)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "reg_req");
    QJsonObject clInfoObject;
    clientInfo.name = clientName;
    clientInfo.write(clInfoObject);
    jsonObject.insert("info", clInfoObject);
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

QByteArray ServerConnection::encryptCreateChannelReply(bool reply, QString clientName, int id)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "req_rep");
    jsonObject.insert("client", clientName);
    jsonObject.insert("result", reply ? "acc" : "rej");
    jsonObject.insert("id", id);
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

/*QByteArray ServerConnection::encryptClientInfo()
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "cli_info");
    clientInfo.write(jsonObject);
    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);
}*/

QByteArray ServerConnection::encryptSendSymKey()
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "set_key");
    jsonObject.insert("key",  gcm.getKey());

    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return otherRsa.encryptMessage(array);
}

QByteArray ServerConnection::encryptSendQuit()
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "quit");
    QJsonDocument jsonDoc(jsonObject);
    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);

}

void ServerConnection::sendSymKey()
{
    socket->write(encryptSendSymKey());
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
    encrypted = true;

}

void ServerConnection::socketStateChanged(QAbstractSocket::SocketState state)
{

}

void ServerConnection::socketError(QAbstractSocket::SocketError error)
{

}

void ServerConnection::sslErrors(QList<QSslError> errors)
{

}

bool ServerConnection::initialize(){
    int res;
    gcm.initialize();

    if ((res = gcm.generateGcmKey()) != 0){
        qDebug() << "could not generate key: " << res;
        return false;
    }

    qDebug() << "key is: " << gcm.getKey();

    if ((res = otherRsa.initialize()) != 0){
        qDebug() << "could not initialize other rsa: " << res;
        return false;
    }
    if ((res = otherRsa.setPartnerPublicKeyFromFile(serverPubKeyPath)) != 0){
        qDebug() << "could not load server public key form file: " << res;
        return false;
    }

    socket = new QSslSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(socketError(QAbstractSocket::SocketError)));
            connect(socket, SIGNAL(sslErrors(QList<QSslError>)),
    this, SLOT(sslErrors(QList<QSslError>)));
    return true;
}

void ServerConnection::connectToServer(QString serverAddress, quint16 port)
{
    socket->setProtocol(QSsl::SslV3);

    QFile serverCertFile("server.crs");
    if (! serverCertFile.open(QIODevice::ReadOnly)){
        qDebug() << "could not open certificate file";
        return;
    }
    QSslCertificate serverCert(&serverCertFile, QSsl::Pem);
    socket->addCaCertificate(serverCert);

    socket->connectToHostEncrypted(serverAddress, port);


    if (!socket->waitForEncrypted()){
        qDebug() << "could not securely connect to the server!!";
        return;
    }

}

/*unsigned char* ServerConnection::generateGcmKey()
{
    return gcm.generateGcmKey();
}*/

/*void ServerConnection::setkey(unsigned char * newKey)
{
    gcm.setKey(newKey);

}*/

/*ServerConnection::~ServerConnection()
{

}*/

void ServerConnection::connected()
{
    qDebug() << "connected";
}

void ServerConnection::readyRead()
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
           if (type == "ret_cli"){
                qDebug() << "returned get clients";
                auto clients = parser.getRegisteredClients();
                for (auto it : clients){
                    qDebug() << it.toString();
                }
                emit onUpdatedActiveClients(clients);
           }else
           if (type == "req_cre"){
               ClientInfo clInfo = parser.getClientInfo();
               qDebug() << "received request for communication from: client: " << clInfo.name;

               emit onRequestReceived(clInfo);
           }else
           if (type == "req_rep"){
               //QString client = parser.get("client");
               QString res = parser.get("result");
               ClientInfo clInfo = parser.getClientInfo();
               int id = parser.getJson()["id"].toInt();
               qDebug() << "received reply for communication from: client: " << clInfo.name << "  with id: " << id;
               bool acc = res == "acc" ? true :false;
               emit onChannelReplyReceived(clInfo, acc, id);
           }else
           if (type == "reg_rep"){
               QString result = parser.get("result");
               QString name = parser.get("name");
               qDebug() << "received reply for registration, result: " << result;
               emit onRegistrationReply(name, result);
           }

       } else {
           // this means that we have received a message before a secure channel was established
           qDebug() << "server connection should never receive message not encrypted by aes";
       }
    }
   buffer.reset();

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

void ServerConnection::sendCreateChannelReply(bool reply, QString clientName, int id)
{
    socket->write(encryptCreateChannelReply(reply, clientName, id));
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}

void ServerConnection::sendGetActiveClientsRequest()
{
    socket->write(encryptGetActiveClientsRequest());
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";
}

void ServerConnection::sendQuit()
{
    if (! encrypted)
        return;
    socket->write(encryptSendQuit());
    if (!socket->waitForBytesWritten())
        qDebug() << "cant write bytes";

}
