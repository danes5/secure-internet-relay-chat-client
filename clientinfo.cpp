#include "clientinfo.h"

ClientInfo::ClientInfo()
{

}

void ClientInfo::write(QJsonObject &json) const
{
    // temporary implementation
    json["address"] = clientAddress;
    json["pub_key"] = publicKey.object();
    json["name"] = name;

}

void ClientInfo::read(const QJsonObject &json)
{
    // temporary implementation
    clientAddress = json["address"].toString();
    //publicKey = QJsonDocument::fromJson( json["pub_key"].toArray());
    publicKey = QJsonDocument(json["pub_key"].toObject());
    name = json["name"].toString();
}

bool ClientInfo::operator ==(const ClientInfo &other)
{
    return name == other.name;
}
