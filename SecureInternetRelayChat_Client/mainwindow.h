#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "clientslistmodel.h"
#include <QTextBrowser>
#include <QListView>
#include <QColumnView>
#include "activecommunicationsmodel.h"
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>

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
    void updateActiveClients(const QList<QString> *clients);
    void onCommunicationClicked(const QModelIndex &index);
    void addCommunication(QString name);
    void removeCommunication(QString name);
    void sendMessageButtonPressed();
    void onStartCommunicationClicked(const QModelIndex &index);
    void onLoginButtonClicked();

signals:
    void forwardSendMessage(QString communication, QString text);
    void forwardStartCommunication(QString clientName);
    void forwardRegisterToServer(QString name);


private:
    Ui::MainWindow *ui;
    Client* client;
    QMap<QString, QString> texts;
    QString activeCommunication;
    ClientsListModel clientsListModel;
    ActiveCommunicationsModel communicationsListModel;
    QTextBrowser *textDisplayer;
    QTextEdit *textEdit;
    QPushButton *sendMessageButton;
    QPushButton *sendFileButton;
    QPushButton *startCommunicationButton;
    QListView *activeClientsView;
    QListView *activeCommunicationsView;
    QLabel *enterNameLabel;
    QLineEdit *enterNameTextEdit;
    QFrame *enterNameFrame;
    QPushButton *enterNameButton;
    QPushButton* quitButton;
    void hideLoginUI();






};

#endif // MAINWINDOW_H
