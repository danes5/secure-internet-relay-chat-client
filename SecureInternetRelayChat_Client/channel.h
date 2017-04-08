#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QSslSocket>
#include "clientinfo.h"
#include "networktransmission.h"
#include "securityfunctions.h"
#include "gcmutils.h"

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
    QString getOtherClientName();
    QByteArray encryptMessage(QString text);
    QJsonDocument decrypt(QByteArray array);


signals:

public slots:
    void processReadyRead();
    void sendMessage(QString message);
    void sendFile(QByteArray data);

private:
    QSslSocket* channelSocket;
    ClientInfo otherClient;
    ChannelStates channelState;
    NetworkTransmission transmission;
    QByteArray buffer;
    // id of the next message expecting from other client
    quint64 id = 0;
    quint64 expectedDataSize;
    bool receivedLength;
    bool receivedTag;

    bool connected;
    GcmUtils gcm;

public:
    void initialize();

    unsigned char * generateGcmKey();
    void setkey(unsigned char * newKey);


};

#endif // CHANNEL_H
