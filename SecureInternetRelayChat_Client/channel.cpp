#include "channel.h"

Channel::Channel(QObject *parent) : QObject(parent)
{

}

QString Channel::getOtherClientName()
{
    return otherClient.clientName;
}

void Channel::processReadyRead()
{

}

void Channel::sendMessage(QString message)
{
    QByteArray m = message.toLatin1();
    channelConnection->write(m);

}

void Channel::sendFile(QByteArray data)
{

}
