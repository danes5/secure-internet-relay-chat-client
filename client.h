#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSslSocket>
#include <QList>
#include "channel.h"
#include "clientinfo.h"
#include "gcmutils.h"
#include "clientserver.h"
#include "serverconnection.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(quintptr port = 5001, QObject *parent = 0);
    enum serverReplyType{
        REGISTER_REPLY,
        GET_ACTIVE_CLIENTS_REPLY,
        RECEIVE_CREATE_CHANNEL_REPLY,
        RECEIVE_CREATE_CHANNEL_REQUEST,
        RECEIVE_CHANNEL_DATA
    };
    const QList<QString>* getActiveClients();

signals:
    void onActiveClientsUpdated(QJsonArray clients);
    void onRegistrationSuccessful();
    void onRegistrationFailed(QString message);
    void onMessageReceivedSignal(QString text, QString otherClient);
    void onChannelRequestReceived(QString name);
    void onChannelActive(QString name);


public slots:
    void updateActiveClients();

    void updatedActiveClients(QJsonArray clients);
    /**
     * @brief sendCreateChannelRequest called from UI, attempts to start communication with other client
     * @param name other client
     */
    void sendCreateChannelRequest(QString name);

    /**
     * @brief receiveCreateChannelRequest receives request from other client and passes it to UI, then send answer back to the server
     * @param name other client
     */
    void receiveCreateChannelRequest(ClientInfo clInfo);


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

    void incomingConnection(quintptr socketDescriptor);

    void messageReceived(QString text, QString otherClient);

    void registrationReplyReceived(QString name, QString result);
    void channelRequestAccepted();
    void channelRequestDeclined();
    void channelActive(QString name);
    /**
     * @brief receiveCreateChannelReply receive reply from other client for request for communication
     */
    void receiveCreateChannelReply(ClientInfo info, bool result, int id);




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

    bool initialize();



    /**
     * @brief receiveCreateChannelData receive data needed to establish communication with other user
     */
    void receiveCreateChannelData();
    void registrationSuccessful();
    void registrationFailed();
    void readingComplete();
    void verifyServerMessageID();
    void processReceivingType();

    const QHostAddress serverAddress;
    QList<QString> activeClients;
    QList<Channel*> activeChannels;
    ClientInfo clientInfo;
    ClientServer clientServer;
    //NetworkTransmission currentTransmission;

    QList<ClientInfo> pendingConnections;
    QList<ClientInfo> expectingConnections;
    QList<int> expectingIds;
    int nextId;


    //const QString serverName;
    //const qint16 port;
    bool isRegistered;
    ServerConnection serverConnection;

    QString pendingClientName;
    ClientInfo pendingClientInfo;
    bool pendingRequest;

    GcmUtils gcm;
    rsautils rsa;








};

#endif // CLIENT_H
