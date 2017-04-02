#include "activecommunicationsmodel.h"

ActiveCommunicationsModel::ActiveCommunicationsModel()
{

}

QVariant ActiveCommunicationsModel::data(const QModelIndex &index, int role) const
{
    return QVariant(_data->keys().at(index.row()));
}

int ActiveCommunicationsModel::rowCount(const QModelIndex &parent) const
{
    return _data->count();
}

void ActiveCommunicationsModel::setSource(const QMap<QString, QString> *src)
{
    _data = src;
}
