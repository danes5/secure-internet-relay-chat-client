#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include <QColumnView>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(Client *cl, QWidget *parent = 0);
  ~MainWindow();

public slots:
  void updateActiveClients(QJsonArray clients);
  void onCommunicationClicked(QListWidgetItem *item);
  void addCommunication(QString name);
  void removeCommunication(QString name);
  void sendMessageButtonPressed();
  void onStartCommunicationClicked();
  void onLoginButtonClicked();
  void hideLoginUI();
  void showLoginError(QString message);
  void clientClicked(QListWidgetItem *item);
  void messageReceived(QString text, QString otherClient);
  void refreshButtonPressed();
  void requestReceived(QString name);
  void channelRequestAccepted();
  void channelRequestDeclined();
  void channelCreated(QString name);
  void quitPressed();
  void channelDeleted(QString name);
  void leaveChannelPressed();

signals:
  void forwardSendMessage(QString communication, QString text);
  void forwardStartCommunication(QString clientName);
  void forwardRegisterToServer(QString name);
  void onRefreshButtonPressed();
  void onChannelRequestAccepted();
  void onChannelRequestDeclined();
  void onQuitPressed();
  void quit();

private:
  Ui::MainWindow *ui;
  Client *client;
  QMap<QString, QString> texts;
  QString activeCommunication;
  QString selectedClient;
  QTextBrowser *textDisplayer;
  QTextEdit *textEdit;
  QPushButton *sendMessageButton;
  QPushButton *startCommunicationButton;
  QLabel *enterNameLabel;
  QLineEdit *enterNameTextEdit;
  QFrame *enterNameFrame;
  QPushButton *enterNameButton;
  QPushButton *quitButton;
  QLabel *loginErrorLabel;
  QListWidget *communicationsList;
  QPushButton *refreshButton;
  QListWidget *clientsList;
  QPushButton *acceptRequestButton;
  QPushButton *declineRequestButton;
  QLabel *requestLabel;
  QPushButton *leaveChannelButton;
};

#endif // MAINWINDOW_H
