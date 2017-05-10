#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <QObject>
#include <QSslSocket>
#include "clientinfo.h"
#include "securityfunctions.h"
#include "gcmutils.h"
#include "parser.h"
#include "buffer.h"
#include "serverinfo.h"
#include "rsautils.h"

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    //ServerConnection();
    explicit ServerConnection(QHostAddress serverAddress, ClientInfo& clInfo, rsautils& rsa, QObject* parent);

    QByteArray encryptRegistrationRequest(QString clientName);
    QByteArray encryptCreateChannelRequest(QString clientName);
    QByteArray encryptCreateChannelReply(bool reply, QString clientName, int id);
    QByteArray encryptGetActiveClientsRequest();
    QByteArray encryptClientInfo();
    QByteArray encryptSendSymKey();
    QByteArray encryptSendQuit();

    const QString serverPubKeyPath = "rsa_pub.txt";

    void sendSymKey();
    void sendRegistrationRequest(QString clientName);
    void sendCreateChannelRequest(QString clientName);
    void sendCreateChannelReply(bool reply, QString clientName, int id);
    void sendGetActiveClientsRequest();
    void sendQuit();



    bool initialize();
    unsigned char * generateGcmKey();
    void setkey(unsigned char * newKey);

    public slots:
    void socketStateChanged(QAbstractSocket::SocketState state);
    //void socketEncrypted();
    void socketError(QAbstractSocket::SocketError error);
    //void sslErrors(QList<QSslError> errors);
    void connected();
    void readyRead();

signals:
    void onRegistrationReply(QString name, QString result);
    void onUpdatedActiveClients(QJsonArray clients);
    void onRequestReceived(ClientInfo clInfo);
    void onChannelReplyReceived(ClientInfo clInfo, bool result, int);

private:
    QTcpSocket* socket;
    GcmUtils gcm;
    ClientInfo& clientInfo;
    Buffer buffer;
    bool encrypted;
    bool hasServerKey;
    quint64 nextId;
    ServerInfo serverInfo;

    bool generateSymKey;
    rsautils& rsa;
    rsautils otherRsa;
    QString authorizationMessage;
    bool otherSideAuthorized;



};

#endif // SERVERCONNECTION_H
