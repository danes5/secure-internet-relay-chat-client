#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QSslSocket>
#include "clientinfo.h"
#include "networktransmission.h"

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QObject *parent = 0);
    enum ChannelStates{
        RECEIVING_MESSAGE,
        RECEIVING_FILE,
        WAITINGFORRECEIVER,
        IDLE
    };

signals:

public slots:
    void processReadyRead();
    void sendMessage(QString message);
    void sendFile(QByteArray data);

private:
    QSslSocket* channelConnection;
    ClientInfo otherClient;
    ChannelStates channelState;
    NetworkTransmission transmission;


};

#endif // CHANNEL_H
