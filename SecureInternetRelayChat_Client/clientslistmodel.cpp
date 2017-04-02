#include "clientslistmodel.h"

ClientsListModel::ClientsListModel()
{

}

int ClientsListModel::rowCount(const QModelIndex &parent) const
{
    return _data->count();
}

void ClientsListModel::setSource(const QList<QString> *src)
{
    _data = src;
}

QVariant ClientsListModel::data(const QModelIndex &index, int role) const
{
    if ( role != Qt::DisplayRole )
        return QVariant();
    return QVariant(_data->at(index.row()));
}
