#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
class Parser
{
public:
    Parser(QJsonDocument doc);
    Parser();
    bool verifyId(quint64 id);
    QString get(const QString& key);
private:
    QJsonObject json;


};

#endif // PARSER_H
