#include "clientinfo.h"

ClientInfo::ClientInfo()
{

}

void ClientInfo::write(QJsonObject &json) const
{
    // temporary implementation
    json["address"] = clientAddress;

}

void ClientInfo::read(const QJsonObject &json)
{
    // temporary implementation
    clientAddress = json["address"].toString();
}
