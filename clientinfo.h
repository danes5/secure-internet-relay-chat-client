#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QHostAddress>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

/**
 * @brief The ClientInfo class
 * class contains essential public information about a client such as their ip address, public key etc.
 */
struct ClientInfo
{
    // ip address of the client
    QString clientAddress;
    // public rsa key of the client
    QJsonDocument publicKey;
    // name of the client
    QString name;


    ClientInfo();
    /**
     * @brief write write ClientInfo data in JSON format
     * @param json
     */
    void write(QJsonObject &json) const;
    /**
     * @brief read JSON data into this object
     * @param json
     */
    void read(const QJsonObject &json);

    bool operator ==(const ClientInfo& other);
};

#endif // CLIENTINFO_H
