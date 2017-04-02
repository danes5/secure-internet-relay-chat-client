#ifndef ACTIVECOMMUNICATIONSMODEL_H
#define ACTIVECOMMUNICATIONSMODEL_H

#include <QObject>
#include "QAbstractListModel"

class ActiveCommunicationsModel : public QAbstractListModel
{
public:
    ActiveCommunicationsModel();
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    void setSource(const  QMap<QString, QString>* src);
private:
    const QMap<QString, QString>* _data;
};

#endif // ACTIVECOMMUNICATIONSMODEL_H
