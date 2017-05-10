#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <QObject>
#include <QSslSocket>
#include "clientinfo.h"
#include "securityfunctions.h"
#include "gcmutils.h"
#include "parser.h"
#include "buffer.h"
#include "rsautils.h"

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    //ServerConnection();
    explicit ServerConnection(ClientInfo& clInfo, rsautils& rsa, QObject* parent);

    /**
     * @brief encryptRegistrationRequest encrypt registration request using symetric key
     * @param clientName requested name
     * @return encrypted message
     */
    QByteArray encryptRegistrationRequest(QString clientName);

    /**
     * @brief encryptCreateChannelRequest encrypt create channel request using symetric key
     * @param clientName name of other client
     * @return encrypted message
     */
    QByteArray encryptCreateChannelRequest(QString clientName);

    /**
     * @brief encryptCreateChannelReply encrypt create channel reply using symetric key
     * @param clientName name of other client
     * @param clientName name of other client
     * @param id identifier for other client to connect to client server
     * @return encrypted message
     */
    QByteArray encryptCreateChannelReply(bool reply, QString clientName, int id);

    /**
     * @brief encryptGetActiveClientsRequest encrypt request to get list of active clients
     * @return encrypted message
     */
    QByteArray encryptGetActiveClientsRequest();

    /**
     * @brief encryptSendSymKey encrypt request to set symetric key using asymetric key
     * @return encrypted message
     */
    QByteArray encryptSendSymKey();

    /**
     * @brief encryptSendQuit encrypt message to quit
     * @return encrypted data
     */
    QByteArray encryptSendQuit();

    const QString serverPubKeyPath = "rsa_pub.txt";

    /**
     * @brief sendSymKey sends encrypted message to set symetric key
     */
    void sendSymKey();

    /**
     * @brief sendRegistrationRequest send encrypted registration request
     * @param clientName requested name
     */
    void sendRegistrationRequest(QString clientName);

    /**
     * @brief sendCreateChannelRequest sends encrypted request to create channel
     * @param clientName name of other client
     */
    void sendCreateChannelRequest(QString clientName);

    /**
     * @brief sendCreateChannelReply sends encrypted reply to create channel request
     * @param reply accept or decline
     * @param clientName name of other client
     * @param id id to connect to
     */
    void sendCreateChannelReply(bool reply, QString clientName, int id);

    /**
     * @brief sendGetActiveClientsRequest sends encrypted request to get active clients
     */
    void sendGetActiveClientsRequest();

    /**
     * @brief sendQuit send encrypted message to remove this client
     */
    void sendQuit();

    /**
     * @brief initialize initializes rsa and gcm
     * @return
     */
    bool initialize();

    /**
     * @brief connectToServer securely connects to the server and sets certificates etc.
     */
    void connectToServer(QString serverAddress, quint16 port);

    public slots:
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketError(QAbstractSocket::SocketError error);
    void sslErrors(QList<QSslError> errors);
    /**
     * @brief connected slot called after connection to server has been established
     */
    void connected();

    /**
     * @brief readyRead slot called after data is available on socket
     */
    void readyRead();

signals:
    /**
     * @brief onRegistrationReply signal emmited after registration reply was received
     * @param name requested name
     * @param result accepted or rejected
     */
    void onRegistrationReply(QString name, QString result);

    /**
     * @brief onUpdatedActiveClients signal emmited after new list of active clients was received
     * @param clients list of clients
     */
    void onUpdatedActiveClients(QJsonArray clients);

    /**
     * @brief onRequestReceived signal emmited after request for communication was received
     * @param clInfo info about sender
     */
    void onRequestReceived(ClientInfo clInfo);

    /**
     * @brief onChannelReplyReceived signal emmited after reply for communication was received
     * @param clInfo info about sender
     * @param result acc or rej
     * @param id identifier to connect to client server
     */
    void onChannelReplyReceived(ClientInfo clInfo, bool result, int id);

private:
    QSslSocket* socket;
    GcmUtils gcm;
    ClientInfo& clientInfo;
    Buffer buffer;
    bool encrypted;
    bool hasServerKey;
    quint64 nextId;

    bool generateSymKey;
    rsautils& rsa;
    rsautils otherRsa;
    QString authorizationMessage;
    bool otherSideAuthorized;



};

#endif // SERVERCONNECTION_H
