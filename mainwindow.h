#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Client* cl, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateActiveClients(QList<QString> clients);
    void onCommunicationClicked(const QModelIndex &index);


private:
    Ui::MainWindow *ui;
    Client* client;
    QMap<QString, QString> texts;
    QString activeCommunication;

};

#endif // MAINWINDOW_H
