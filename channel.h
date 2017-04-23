#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QSslSocket>
#include "clientinfo.h"
#include "securityfunctions.h"
#include "gcmutils.h"
#include "buffer.h"
#include "parser.h"

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(quintptr descriptor, QObject *parent = nullptr);
    explicit Channel(QHostAddress hostAddress, quintptr descriptor, QObject *parent);
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
    void messageReceived(QString text, QString otherClient);

public slots:
    void sendMessage(QString message);
    void sendFile(QByteArray data);
    void readyRead();

private:
    QTcpSocket* socket;
    ClientInfo otherClient;
    ChannelStates channelState;
    Buffer buffer;

    bool connected;
    bool encrypted = true;
    quint64 nextId;
    GcmUtils gcm;

    void connectToHost( quintptr port, const QHostAddress &hostName = QHostAddress::LocalHost);

public:
    void initialize();

    unsigned char * generateGcmKey();
    void setkey(unsigned char * newKey);


};

#endif // CHANNEL_H
