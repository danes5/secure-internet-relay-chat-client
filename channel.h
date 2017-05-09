#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QSslSocket>
#include "clientinfo.h"
#include "securityfunctions.h"
#include "gcmutils.h"
#include "buffer.h"
#include "parser.h"
#include "rsautils.h"

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(ClientInfo otherClient, quintptr descriptor, QObject *parent = nullptr);
    //explicit Channel(QString otherName, QHostAddress hostAddress, quintptr descriptor, QObject *parent);
    explicit Channel(ClientInfo otherClient, QObject *parent = nullptr);
    enum ChannelStates{
        RECEIVING_MESSAGE,
        RECEIVING_FILE,
        WAITINGFORRECEIVER,
        IDLE
    };
    QString getOtherClientName();
    QByteArray encryptMessage(QString text);
    QByteArray encryptSendAuthorizarionMessage(QString message);
    QByteArray encryptSendSymKey(QString key);
    QJsonDocument decrypt(QByteArray array);
    void sendAuthorizationMessage();
    void sendSymetricKey();


signals:
    void onMessageReceived(QString text, QString otherClient);
    void onChannelConnected(QString name);

public slots:
    void sendMessage(QString message);
    void sendFile(QByteArray data);
    void readyRead();

private:
    QTcpSocket* socket;
    //ClientInfo otherClient;
    ChannelStates channelState;
    Buffer buffer;

    bool connected;
    bool encrypted = true;
    quint64 nextId;
    GcmUtils gcm;
    QString otherClientName;
    ClientInfo otherClientInfo;

    bool generateSymKey;
    RsaUtils rsa;
    RsaUtils otherRsa;
    QString authorizationMessage;
    bool otherSideAuthorized;



public:
    void initialize();
    void connectToHost(QString otherName, const QHostAddress &hostAddress = QHostAddress::LocalHost, quintptr port = 5001);

    unsigned char * generateGcmKey();
    void setkey(unsigned char * newKey);



};

#endif // CHANNEL_H
