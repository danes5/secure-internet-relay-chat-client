#include "client.h"

Client::Client(QObject *parent) : QObject(parent), port(4500), serverName("server not yet set up")
{

}

const QList<QString> *Client::getActiveClients()
{
    return &activeClients;

}

void Client::sendCreateChannelRequest(QString name)
{

}

void Client::receiveCreateChannelRequest(QString name)
{

}

void Client::processReadyRead()
{
    QByteArray data = serverConnection->readAll();
    if (! isRegistered)
        return;
    if (! isReceiving){
        isReceiving = true;
        currentReceivingType = (serverReplyType)data.at(0);
        return;

    }

}

void Client::sendMessage(QString dest, QString text)
{
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
    serverConnection = new QSslSocket(this);
    serverConnection->connectToHostEncrypted(serverName, port);
    currentReceivingType = REGISTER_REPLY;
}

QList<QString> Client::getActiveNamesFromServer()
{

}

void Client::acceptCreateChannelRequest(QString name)
{

}

void Client::updateActiveClients(){

}
