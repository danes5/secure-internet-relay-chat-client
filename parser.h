#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QJsonArray>
class Parser
{
public:
    Parser(QJsonDocument doc);
    Parser();
    bool verifyId(quint64 id);
    QString get(const QString& key);
    QJsonArray getRegisteredClients();
private:
    QJsonObject json;


};

#endif // PARSER_H
