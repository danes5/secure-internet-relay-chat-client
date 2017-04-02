#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSslSocket>
#include <QList>
#include "channel.h"
#include "clientinfo.h"

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

signals:
    void activeClientsUpdated(QList<QString> activeClients);

public slots:
    void updateActiveClients();
    void sendCreateChannelRequest(QString name);
    void receiveCreateChannelRequest(QString name);
    void processReadyRead();


private:

    /**
     * @brief registerToServer attempts to register to client
     * may fail for example if there is no connection to the server
     * or if client with same username already exists
     */
    void registerToServer();

    /**
     * @brief getActiveNames gets active clients from server
     * @return active clients
     */
    QList<QString> getActiveNames();

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

    bool isRegistered;
    bool isReceiving;
    serverReplyType currentReceivingType;
    QSslSocket* serverConnection;
    QList<QString> activeClients;
    QList<Channel*> activeChannels;
    ClientInfo clientInfo;
    NetworkTransmission currentTransmission;




};

#endif // CLIENT_H
