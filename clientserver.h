#ifndef CLIENTSERVER_H
#define CLIENTSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QThread>
//#include "Connection.h"
#include <map>
#include <string>
//#include "Client.hpp"

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

/**
 * @brief The ClientServer class
 * class that accepts connections on the client side and forwards them co client class
 */
class ClientServer : public QTcpServer
{
    Q_OBJECT
public:
    ClientServer(quintptr port, QObject* parent = nullptr);
protected:
    /**
     * @brief incomingConnection raised after attempt to connect to client server
     * @param socketDescriptor
     */
    void incomingConnection(qintptr socketDescriptor) override;
signals:
    /**
     * @brief incomingConnectionSignal signal raised after new connection
     * @param socketDescriptor
     */
    void incomingConnectionSignal(quintptr socketDescriptor);
};

#endif // CLIENTSERVER_H
