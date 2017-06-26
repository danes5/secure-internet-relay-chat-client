#ifndef CLIENTSLISTVIEW_H
#define CLIENTSLISTVIEW_H

#include <QAbstractListModel>
#include <QObject>

class clientsListView : QAbstractListModel {
public:
  clientsListView();
  QVariant QAbstractItemModel::data(const QModelIndex &index,
                                    int role = Qt::DisplayRole) const;
  int QAbstractItemModel::rowCount(
      const QModelIndex &parent = QModelIndex()) const;

private:
  QList<QString> *data;
};

#endif // CLIENTSLISTVIEW_H
