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
    explicit Channel(QList<ClientInfo> *connections, QList<int> *ids, quintptr descriptor, bool genKey, rsautils& rsa, QObject *parent);
    //explicit Channel(QString otherName, QHostAddress hostAddress, quintptr descriptor, QObject *parent);
    explicit Channel(ClientInfo otherClient, bool genKey, rsautils& rsa, QObject *parent);
    /**
     * @brief getOtherClientName
     * @return name of the client this channel is connected to
     */
    QString getOtherClientName();
    /**
     * @brief encryptMessage prepares text message to send over network
     * @param text text to encrypt
     * @return ecrypted byte array
     */
    QByteArray encryptMessage(QString text);

    /**
     * @brief encryptSendAuthorizarionMessage prepares authorization text to send over network
     * @param message authorization text to encrypt
     * @return ecrypted byte array
     */
    QByteArray encryptSendAuthorizarionMessage(QString message);

    /**
     * @brief encryptSendSymKey prepare symetric key to be sent over the network
     * @param key key to encrypt
     * @return ecrypted byte array
     */
    QByteArray encryptSendSymKey(QString key);

    /**
     * @brief decrypt decrypt message using symetric key
     * @param array encrypted data
     * @return decrypted data
     */
    QJsonDocument decrypt(QByteArray array);

    /**
     * @brief sendAuthorizationMessage send authorization text to other client
     */
    void sendAuthorizationMessage();

    /**
     * @brief sendSymetricKey send symetric key to other client
     */
    void sendSymetricKey();

    /**
     * @brief sendId send identifier to other client
     * @param id
     */
    void sendId(int id);

    /**
     * @brief initialize initializes gcm and rsa modules
     */
    void initialize();
    /**
     * @brief connectToHost attempt to connect to client server on port
     * @param port port to connect to
     */
    void connectToHost(quintptr port = 5001);

    /**
     * @brief generateGcmKey generates and sets key
     * @return key generated
     */
    unsigned char * generateGcmKey();
    /**
     * @brief setkey set key to value
     * @param newKey key to set
     */
    void setkey(unsigned char * newKey);


signals:
    /**
     * @brief onMessageReceived signal raised when message is received on this channel
     * @param text text received
     * @param otherClient sender of the message
     */
    void onMessageReceived(QString text, QString otherClient);
    //void onChannelConnected(QString name);

    /**
     * @brief onChannelActive signal raised when channel becomes active
     * @param name name of this channel
     */
    void onChannelActive(QString name);

public slots:
    /**
     * @brief sendMessage send message over network
     * @param message
     */
    void sendMessage(QString message);

    /**
     * @brief sendFile send file over network
     * @param data
     */
    void sendFile(QByteArray data);

    /**
     * @brief readyRead triggered when data is available on socket
     */
    void readyRead();

private:
    QTcpSocket* socket;
    Buffer buffer;

    bool connected;
    bool encrypted;
    quint64 nextId;
    GcmUtils gcm;
    ClientInfo otherClientInfo;

    bool generateSymKey;
    rsautils &rsa;
    rsautils otherRsa;
    QString authorizationMessage;
    bool otherSideAuthorized;
    bool hasInfo;
    /**
     * @brief pointer to expecting connextions
     */
    QList<ClientInfo> * connections;
    /**
     * @brief ids pointer to expecting ids
     */
    QList<int> * ids;







};

#endif // CHANNEL_H
