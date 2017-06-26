#ifndef PARSER_H
#define PARSER_H

#include "clientinfo.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QObject>
class Parser {
public:
  Parser(QJsonDocument doc);
  Parser();
  bool verifyId(quint64 id);
  QString get(const QString &key);
  QJsonArray getRegisteredClients();
  ClientInfo getClientInfo();
  QJsonObject getJson();
  int getId();

private:
  QJsonObject json;
};

#endif // PARSER_H
