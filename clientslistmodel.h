#ifndef CLIENTSLISTVIEW_H
#define CLIENTSLISTVIEW_H

#include <QObject>
#include <QAbstractListModel>

class ClientsListModel : public QAbstractListModel
{
public:
    ClientsListModel();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    void setSource(const QList<QString> * src);
private:
    const QList<QString> *_data;
};

#endif // CLIENTSLISTVIEW_H
