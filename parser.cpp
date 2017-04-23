#include "parser.h"
#include <QDebug>

Parser::Parser(QJsonDocument doc)
{
    json = doc.object();
}

Parser::Parser()
{

}

bool Parser::verifyId(quint64 id)
{
    return true;
    //return json["id"].toString().toULongLong() == id;


}

QString Parser::get(const QString &key)
{
    return json[key].toString();
}
