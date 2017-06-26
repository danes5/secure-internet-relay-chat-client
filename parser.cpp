#include "parser.h"
#include <QDebug>

Parser::Parser(QJsonDocument doc) { json = doc.object(); }

Parser::Parser() {}

bool Parser::verifyId(quint64 id) {
  (void)id;
  return true;
}

QString Parser::get(const QString &key) { return json[key].toString(); }

ClientInfo Parser::getClientInfo() {
  ClientInfo clInfo;
  QJsonObject infoObject = json["info"].toObject();
  clInfo.read(infoObject);
  return clInfo;
}

QJsonArray Parser::getRegisteredClients() {
  QJsonObject jsonClients = json["data"].toObject();
  QJsonArray names = jsonClients["names"].toArray();
  return names;
}

QJsonObject Parser::getJson() { return json; }

int Parser::getId() { return json["id"].toInt(); }
