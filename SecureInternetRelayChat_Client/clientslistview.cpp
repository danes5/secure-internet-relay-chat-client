#include "clientslistview.h"

clientsListView::clientsListView()
{

}

int clientsListView::QAbstractItemModel::rowCount(const QModelIndex &parent) const
{
    return data->count();
}

QVariant clientsListView::QAbstractItemModel::data(const QModelIndex &index, int role) const
{
    return QVariant(data->at(index));
}
