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
 * not yet fully implemented
 */
struct ClientInfo
{
    // ip address of the client
    QHostAddress clientAddress;

    // class should contain some additional info about client

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
};

#endif // CLIENTINFO_H
