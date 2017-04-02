#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

void Client::sendCreateChannelRequest(QString name)
{

}

void Client::processReadyRead()
{
    QByteArray data = serverConnection->readAll();
    if (! isRegistered)
        return;
    if (! isReceiving){
        isReceiving = true;
        currentReceivingType = (serverReplyType)data[0];
        data.remove(0, 1);

    }

}

void Client::registerToServer()
{
}

QList<QString> Client::getActiveNames()
{

}

void Client::acceptCreateChannelRequest(QString name)
{

}
