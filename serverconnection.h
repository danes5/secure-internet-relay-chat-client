#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <QObject>
#include <QSslSocket>
#include "clientinfo.h"
#include "securityfunctions.h"
#include "gcmutils.h"
#include "parser.h"
#include "buffer.h"

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    //ServerConnection();
    explicit ServerConnection(QObject* parent);

    QByteArray encryptRegistrationRequest(QString clientName);
    QByteArray encryptCreateChannelRequest(QString clientName);
    QByteArray encryptCreateChannelReply(bool reply, QString clientName);
    QByteArray encryptGetActiveClientsRequest();
    QByteArray encryptClientInfo();

    void sendRegistrationRequest(QString clientName);
    void sendCreateChannelRequest(QString clientName);
    void sendCreateChannelReply(bool reply, QString clientName);
    void sendGetActiveClientsRequest();



    void initialize();
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

private:
    QTcpSocket* socket;
    GcmUtils gcm;
    ClientInfo clientInfo;
    Buffer buffer;
    bool encrypted = true;
    quint64 nextId;



};

#endif // SERVERCONNECTION_H
