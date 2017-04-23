#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QJsonArray>
#include "clientinfo.h"
class Parser
{
public:
    Parser(QJsonDocument doc);
    Parser();
    bool verifyId(quint64 id);
    QString get(const QString& key);
    QJsonArray getRegisteredClients();
    ClientInfo getClientInfo();
private:
    QJsonObject json;


};

#endif // PARSER_H
