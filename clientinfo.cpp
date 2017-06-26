#include "clientinfo.h"

ClientInfo::ClientInfo() {}

void ClientInfo::write(QJsonObject &json) const {
  json["address"] = clientAddress;
  json["pub_key"] = publicKey.object();
  json["name"] = name;
}

void ClientInfo::read(const QJsonObject &json) {
  clientAddress = json["address"].toString();
  publicKey = QJsonDocument(json["pub_key"].toObject());
  name = json["name"].toString();
}

bool ClientInfo::operator==(const ClientInfo &other) {
  return name == other.name;
}
