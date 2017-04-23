#include "client.h"
#include <QNetworkInterface>

Client::Client(quintptr port, QObject *parent) : QObject(parent), serverAddress(QString("192.168.0.45")),
    clientServer(port, this), serverConnection(serverAddress, clientInfo, this)
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             clientInfo.clientAddress = address.toString();
    }
    connect(&clientServer, SIGNAL(incomingConnectionSignal(quintptr)), this, SLOT(incomingConnection(quintptr)));
    connect( &serverConnection, SIGNAL(onRegistrationReply(QString,QString)), this, SLOT(registrationReplyReceived(QString, QString)));
    connect(&serverConnection, SIGNAL(onUpdatedActiveClients(QJsonArray)), this, SLOT(updatedActiveClients(QJsonArray)));
    connect( &serverConnection, SIGNAL(onRequestReceived(QString, ClientInfo)), this, SLOT(receiveCreateChannelRequest(QString,ClientInfo)));

}

const QList<QString> *Client::getActiveClients()
{
    return &activeClients;

}


void Client::sendCreateChannelRequest(QString name)
{
    qDebug() << "sending create channel request to the server\n";
    serverConnection.sendCreateChannelRequest(name);
    pendingClientName = name;
}

/*void Client::initialize(){
    gcm.initialize();
}

unsigned char* Client::generateGcmKey()
{
    return gcm.generateGcmKey();
}

void Client::setkey(unsigned char * newKey)
{
    gcm.setKey(newKey);

}*/




void Client::receiveCreateChannelRequest(QString name, ClientInfo clInfo)
{
    qDebug() << "received create channel request";
    pendingRequest = true;
    pendingClientName = name;
    pendingClientInfo = clInfo;
    emit onChannelRequestReceived(name);

}


void Client::sendMessage(QString dest, QString text)
{
    qDebug() << "sending message";
    foreach (Channel* channel, activeChannels) {
        if (channel->getOtherClientName() == dest){
            channel->sendMessage(text);
            return;
        }
    }
    // open channel for client not found, which means inconsistenct between our UI and client class.
    qWarning() << "client not found\n";
}

void Client::registerToServer(QString name)
{
    serverConnection.sendRegistrationRequest(name);

    /*
    serverConnection = new QSslSocket(this);

    connect(serverConnection, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                    this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
            connect(serverConnection, SIGNAL(encrypted()),
                    this, SLOT(socketEncrypted()));
            connect(serverConnection, SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(socketError(QAbstractSocket::SocketError)));
            connect(serverConnection, SIGNAL(sslErrors(QList<QSslError>)),
                    this, SLOT(sslErrors(QList<QSslError>)));
            connect(serverConnection, SIGNAL(readyRead()),
                    this, SLOT(processReadyRead()));

    serverConnection->connectToHostEncrypted(serverName, port);
    //currentReceivingType = REGISTER_REPLY;*/
}

void Client::incomingConnection(quintptr socketDescriptor)
{
    qDebug() << "incoming connection by connecting to client server on port: " << socketDescriptor;
    // here we have to somehow verify whether the host attemptint to connect is the host that we accepted the request from
    Channel* channel = new Channel(pendingClientName, socketDescriptor, this);
    connect(channel, SIGNAL(onMessageReceived(QString, QString)), this, SLOT(messageReceived(QString, QString)));
    //connect(channel, SIGNAL(onChannelConnected(QString)), this, SLOT(channelConnected(QString)));
    activeChannels.push_back(channel);
    emit onChannelConnected(pendingClientName);
}

void Client::messageReceived(QString text, QString otherClient)
{
    qDebug() << "message received slot!";
    emit onMessageReceivedSignal(text, otherClient);
}

void Client::registrationReplyReceived(QString name, QString result)
{
    qDebug() << "client registraion reply received";
    bool reg = result == "acc" ? true : false;
    if (!isRegistered)
        isRegistered = reg;

    if (isRegistered){
        emit onRegistrationSuccessful();
    }else{
        emit onRegistrationFailed("registration failed, try again");
    }
}

void Client::channelRequestAccepted()
{
    qDebug() << "channel request accepted by user on client";
    Channel* channel = new Channel(pendingClientName, this);
    connect(channel, SIGNAL(onMessageReceived(QString, QString)), this, SLOT(messageReceived(QString, QString)));
    connect(channel, SIGNAL(onChannelConnected(QString)), this, SLOT(channelConnected(QString)));
    channel->connectToHost(pendingClientName, QHostAddress(pendingClientInfo.clientAddress));
    activeChannels.push_back(channel);

}

void Client::channelRequestDeclined()
{
    qDebug() << "channel request declined by user on client";
}

void Client::channelConnected(QString name)
{
    qDebug() << "CLient:: channel connected";
    emit onChannelConnected(name);
}

/*void Client::socketStateChanged(QAbstractSocket::SocketState state)
{

}

void Client::socketEncrypted()
{
    // now we actually perform sending registration request
}

void Client::socketError(QAbstractSocket::SocketError error)
{
    qDebug() << "socket error: " << error;
}

void Client::sslErrors(QList<QSslError> errors)
{
    foreach (QSslError error, errors) {
        qDebug() << error.errorString();
    }

}*/

QList<QString> Client::getActiveNamesFromServer()
{

}

void Client::acceptCreateChannelRequest(QString name)
{

}

void Client::registrationSuccessful()
{
       emit onRegistrationSuccessful();
    isRegistered = true;
}

void Client::registrationFailed()
{

}

void Client::verifyServerMessageID()
{

}


void Client::updateActiveClients(){
    qDebug() << "client update active clients";
    serverConnection.sendGetActiveClientsRequest();

}

void Client::updatedActiveClients(QJsonArray clients)
{
    emit onActiveClientsUpdated(clients);
}
