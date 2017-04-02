#include "activecommunicationsmodel.h"
#include <QDebug>

ActiveCommunicationsModel::ActiveCommunicationsModel()
{

}

QVariant ActiveCommunicationsModel::data(const QModelIndex &index, int role) const
{
    if ( role != Qt::DisplayRole )
        return QVariant();
    return QVariant(_data->keys().at(index.row()));
}

int ActiveCommunicationsModel::rowCount(const QModelIndex &parent) const
{
    //qDebug() << _data->count();
    return _data->count();
}

void ActiveCommunicationsModel::setSource(const QMap<QString, QString> *src)
{
    _data = src;
}
