#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSslSocket>
#include <QList>
#include "channel.h"
#include "clientinfo.h"
#include "receivingactions.h"
#include <QMessageBox>
#include "gcmutils.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    enum serverReplyType{
        REGISTER_REPLY,
        GET_ACTIVE_CLIENTS_REPLY,
        RECEIVE_CREATE_CHANNEL_REPLY,
        RECEIVE_CREATE_CHANNEL_REQUEST,
        RECEIVE_CHANNEL_DATA
    };
    const QList<QString>* getActiveClients();
    QByteArray encryptRegistrationRequest(QString clientName);
    QByteArray encryptCreateChannelRequest(QString clientName);
    QByteArray encryptCreateChannelReply(bool reply, QString clientName);
    QByteArray encryptGetActiveClientsRequest();
    QByteArray encryptClientInfo();

    void initialize();

    unsigned char * generateGcmKey();
    void setkey(unsigned char * newKey);


signals:
    void activeClientsUpdated(const QList<QString>* activeClients);
    void onRegistrationSuccessful();
    void onRegistrationFailed(QString message);

public slots:
    void updateActiveClients();
    /**
     * @brief sendCreateChannelRequest called from UI, attempts to start communication with other client
     * @param name other client
     */
    void sendCreateChannelRequest(QString name);

    /**
     * @brief receiveCreateChannelRequest receives request from other client and passes it to UI, then send answer back to the server
     * @param name other client
     */
    void receiveCreateChannelRequest(QString name);

    /**
     * @brief processReadyRead this slot is called every time there is some data on packet form server to read
     * method is responsible for parsing the packet, and either setting up structures for incoming data or when already
     * receiving the add data to the buffer until the buffer is full
     */
    void processReadyRead();

    /**
     * @brief sendMessage attempts to send messsage to client with whom connection has already been established
     * @param dest name of the other client
     * @param text text to send
     */
    void sendMessage(QString dest, QString text);

    /**
     * @brief registerToServer attempts to register to client
     * may fail for example if there is no connection to the server
     * or if client with same username already exists
     */
    void registerToServer(QString name);


    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketEncrypted();
    void socketError(QAbstractSocket::SocketError error);
    void sslErrors(QList<QSslError> errors);



private:

    /**
     * @brief getActiveNames gets active clients from server
     * @return active clients
     */
    QList<QString> getActiveNamesFromServer();

    /**
     * @brief acceptCreateChannelRequest accept request for communication from other client
     * @param name name of the other client
     */
    void acceptCreateChannelRequest(QString name);

    /**
     * @brief declineCreateChannelRequest decline accept for communication from other client
     * @param name name of the other client
     */
    void declineCreateChannelRequest(QString name);

    /**
     * @brief receiveCreateChannelReply receive reply from other client for request for communication
     */
    void receiveCreateChannelReply(bool accepted);

    /**
     * @brief receiveCreateChannelData receive data needed to establish communication with other user
     */
    void receiveCreateChannelData();
    void registrationSuccessful();
    void registrationFailed();
    void readingComplete();
    void verifyServerMessageID();
    void processReceivingType();
    ReceivingActions receivingAction;
    quint64 id;
    QString currentReceivingType;
    quint64 expectedDataSize;
    QSslSocket* serverConnection;
    QList<QString> activeClients;
    QList<Channel*> activeChannels;
    ClientInfo clientInfo;
    NetworkTransmission currentTransmission;

    const QString serverName;
    const qint16 port;
    QByteArray buffer;
    bool isRegistered;

    GcmUtils gcm;






};

#endif // CLIENT_H
