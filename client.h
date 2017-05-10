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
    explicit Client(QObject *parent = 0);
    /**
     * @brief getActiveClients
     * @return names of active clients
     */
    const QList<QString>* getActiveClients();

signals:
    /**
     * @brief onActiveClientsUpdated signal emmited when active clients changed
     * @param clients list of clients
     */
    void onActiveClientsUpdated(QJsonArray clients);

    /**
     * @brief onRegistrationSuccessful signal emmited after registration was successful
     */
    void onRegistrationSuccessful();

    /**
     * @brief onRegistrationFailed signall emmited after registration failed
     * @param message error message
     */
    void onRegistrationFailed(QString message);

    /**
     * @brief onMessageReceivedSignal signal emmited after message was received
     * @param text message
     * @param otherClient sender of the message
     */
    void onMessageReceivedSignal(QString text, QString otherClient);

    /**
     * @brief onChannelRequestReceived signal emmited when received request to start communication from other client
     * @param name other client
     */
    void onChannelRequestReceived(QString name);

    /**
     * @brief onChannelActive signal emmited when channel is ready to send messages
     * @param name other client
     */
    void onChannelActive(QString name);

    /**
     * @brief quit signal emmited when received quit from ui
     */
    void quit();


public slots:

    /**
     * @brief updateActiveClients update active clients, called after after user querried for list of active clients
     */
    void updateActiveClients();

    /**
     * @brief updatedActiveClients called after list of active clients was received from server
     * @param clients list of active clients
     */
    void updatedActiveClients(QJsonArray clients);

    /**
     * @brief sendCreateChannelRequest called from UI, attempts to start communication with other client
     * @param name other client
     */
    void sendCreateChannelRequest(QString name);

    /**
     * @brief receiveCreateChannelRequest receives request from other client and raises signal for ui
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

    /**
     * @brief incomingConnection called after new connection was raised on the client server
     * @param socketDescriptor
     */
    void incomingConnection(quintptr socketDescriptor);

    /**
     * @brief messageReceived slot called after message was received, emits signal for ui
     * @param text message received
     * @param otherClient sender of message
     */
    void messageReceived(QString text, QString otherClient);

    /**
     * @brief registrationReplyReceived slot called after registration reply was received from server
     * @param name requested name
     * @param result registration success
     */
    void registrationReplyReceived(QString name, QString result);

    /**
     * @brief channelRequestAccepted slot called from ui after client accepted communication request
     */
    void channelRequestAccepted();

    /**
     * @brief channelRequestAccepted slot called from ui after client accepted communication request
     */
    void channelRequestDeclined();

    /**
     * @brief channelActive slot called after channel becomes active so user can write messages
     */
    void channelActive(QString name);

    /**
     * @brief receiveCreateChannelReply receive reply from other client for request for communication
     * @param info info about other client
     * @param result request status
     * @param id identifier to use when connecting to other client server
     */
    void receiveCreateChannelReply(ClientInfo info, bool result, int id);

    /**
     * @brief quitPressed slot called from ui after quit was pressed
     */
    void quitPressed();


private:

    /**
     * @brief initialize initialize rsa and clientInfo
     * @return success of initialization
     */
    bool initialize();

    void registrationSuccessful();
    void registrationFailed();

    const QString serverAddress;
    const quint16 port;
    QList<QString> activeClients;
    QList<Channel*> activeChannels;
    ClientInfo clientInfo;
    ClientServer clientServer;

    QList<ClientInfo> pendingConnections;
    QList<ClientInfo> expectingConnections;
    QList<int> expectingIds;
    int nextId;

    bool isRegistered;
    ServerConnection serverConnection;

    GcmUtils gcm;
    rsautils rsa;








};

#endif // CLIENT_H
