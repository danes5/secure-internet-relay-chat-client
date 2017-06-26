#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <iostream>

MainWindow::MainWindow(Client *cl, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  client = cl;
  textDisplayer = ui->textDisplayer;
  textEdit = ui->textEdit;
  sendMessageButton = ui->sendMessageButton;
  startCommunicationButton = ui->startCommunicationsButton;
  enterNameButton = ui->enterNameButton;
  enterNameFrame = ui->enterNameFrame;
  enterNameLabel = ui->enterNameLabel;
  enterNameTextEdit = ui->enterNameEdit;
  quitButton = ui->quitButton;
  loginErrorLabel = ui->loginErrorLabel;
  refreshButton = ui->refreshButton;
  loginErrorLabel->setVisible(false);
  communicationsList = ui->communicationsWidget;
  communicationsList->setVisible(false);
  textDisplayer->setVisible(false);
  startCommunicationButton->setVisible(false);
  refreshButton->setVisible(false);
  clientsList = ui->clientsList;
  clientsList->setVisible(false);
  acceptRequestButton = ui->acceptRequestButton;
  declineRequestButton = ui->declineRequestButton;
  acceptRequestButton->setVisible(false);
  declineRequestButton->setVisible(false);
  requestLabel = ui->requestLabel;
  requestLabel->setVisible(false);
  leaveChannelButton = ui->leaveChannelButton;

  // connects signal from client that list of active users has changed with slot
  // in this class which updates it
  connect(client, SIGNAL(onActiveClientsUpdated(QJsonArray)), this,
          SLOT(updateActiveClients(QJsonArray)));
  connect(communicationsList, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(onCommunicationClicked(QListWidgetItem *)));
  connect(clientsList, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(clientClicked(QListWidgetItem *)));
  connect(sendMessageButton, SIGNAL(pressed()), this,
          SLOT(sendMessageButtonPressed()));
  connect(this, SIGNAL(forwardSendMessage(QString, QString)), client,
          SLOT(sendMessage(QString, QString)));
  connect(this, SIGNAL(forwardStartCommunication(QString)), client,
          SLOT(sendCreateChannelRequest(QString)));
  connect(enterNameButton, SIGNAL(pressed()), this,
          SLOT(onLoginButtonClicked()));
  connect(startCommunicationButton, SIGNAL(pressed()), this,
          SLOT(onStartCommunicationClicked()));
  connect(this, SIGNAL(forwardRegisterToServer(QString)), client,
          SLOT(registerToServer(QString)));
  connect(quitButton, SIGNAL(clicked()), this, SLOT(quitPressed()));
  connect(client, SIGNAL(quit()), this, SIGNAL(quit()));
  QObject::connect(this, SIGNAL(quit()), QApplication::instance(),
                   SLOT(quit()));
  connect(this, SIGNAL(onQuitPressed()), client, SLOT(quitPressed()));
  connect(client, SIGNAL(onRegistrationSuccessful()), this,
          SLOT(hideLoginUI()));
  connect(client, SIGNAL(onRegistrationFailed(QString)), this,
          SLOT(showLoginError(QString)));
  connect(client, SIGNAL(onMessageReceivedSignal(QString, QString)), this,
          SLOT(messageReceived(QString, QString)));
  connect(this, SIGNAL(onRefreshButtonPressed()), client,
          SLOT(updateActiveClients()));
  connect(refreshButton, SIGNAL(pressed()), this, SLOT(refreshButtonPressed()));
  connect(acceptRequestButton, SIGNAL(pressed()), this,
          SLOT(channelRequestAccepted()));
  connect(declineRequestButton, SIGNAL(pressed()), this,
          SLOT(channelRequestDeclined()));
  connect(client, SIGNAL(onChannelRequestReceived(QString)), this,
          SLOT(requestReceived(QString)));
  connect(this, SIGNAL(onChannelRequestAccepted()), client,
          SLOT(channelRequestAccepted()));
  connect(this, SIGNAL(onChannelRequestDeclined()), client,
          SLOT(channelRequestDeclined()));
  connect(client, SIGNAL(onChannelActive(QString)), this,
          SLOT(channelCreated(QString)));
  connect(client, SIGNAL(channelDeleted(QString)), this,
          SLOT(channelDeleted(QString)));
  connect(leaveChannelButton, SIGNAL(pressed()), this,
          SLOT(leaveChannelPressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateActiveClients(QJsonArray clients) {
  clientsList->clear();
  for (auto cl : clients) {
    new QListWidgetItem(cl.toString(), clientsList);
  }
}

void MainWindow::onCommunicationClicked(QListWidgetItem *item) {
  qDebug() << "on communication clicked";
  activeCommunication = item->text();
  textDisplayer->setText(*texts.find(item->text()));
}

void MainWindow::addCommunication(QString name) {
  qDebug() << "main window add communication";
  texts.insert(name, "");
}

void MainWindow::removeCommunication(QString name) { texts.remove(name); }

void MainWindow::sendMessageButtonPressed() {
  QString text = textEdit->toPlainText();
  textEdit->clear();
  texts[activeCommunication].append("you> " + text + "\n");
  textDisplayer->setText(texts[activeCommunication]);
  emit forwardSendMessage(activeCommunication, text);
}

void MainWindow::onStartCommunicationClicked() {
  qDebug() << "start communication emmmited";
  emit forwardStartCommunication(selectedClient);
}

void MainWindow::onLoginButtonClicked() {
  QString name = enterNameTextEdit->text();
  emit forwardRegisterToServer(name);
}

void MainWindow::showLoginError(QString message) {
  loginErrorLabel->setText(message);
  loginErrorLabel->setVisible(true);
}

void MainWindow::clientClicked(QListWidgetItem *item) {
  selectedClient = item->text();
}

void MainWindow::messageReceived(QString text, QString otherClient) {
  qDebug() << "main window message received from: " << otherClient;
  texts[otherClient].append(text);
  if (communicationsList->findItems(otherClient, Qt::MatchExactly).isEmpty())
    new QListWidgetItem(otherClient, communicationsList);
  if (activeCommunication == otherClient) {
    textDisplayer->setText(*texts.find(activeCommunication));
  }
}

void MainWindow::refreshButtonPressed() { emit onRefreshButtonPressed(); }

void MainWindow::requestReceived(QString name) {
  acceptRequestButton->setVisible(true);
  declineRequestButton->setVisible(true);
  requestLabel->setVisible(true);
  requestLabel->setText(QString("Received request from user: " + name));
}

void MainWindow::channelRequestAccepted() {
  acceptRequestButton->setVisible(false);
  declineRequestButton->setVisible(false);
  requestLabel->setVisible(false);
  emit onChannelRequestAccepted();
}

void MainWindow::channelRequestDeclined() {
  acceptRequestButton->setVisible(false);
  declineRequestButton->setVisible(false);
  requestLabel->setVisible(false);
  emit onChannelRequestDeclined();
}

void MainWindow::channelCreated(QString name) {
  qDebug() << "created channel with: " << name;
  texts.insert(name, "");
  new QListWidgetItem(name, communicationsList);
}

void MainWindow::quitPressed() { emit onQuitPressed(); }

void MainWindow::channelDeleted(QString name) {
  qDebug() << "channel deleted main window";
  texts.remove(name);
  if (activeCommunication == name)
    textDisplayer->setText("");
  qDeleteAll(communicationsList->findItems(name, Qt::MatchExactly));
}

void MainWindow::leaveChannelPressed() {
  emit client->leaveChannel(activeCommunication);
}

void MainWindow::hideLoginUI() {
  loginErrorLabel->setVisible(false);
  enterNameLabel->setVisible(false);
  enterNameButton->setVisible(false);
  enterNameFrame->setVisible(false);
  enterNameTextEdit->setVisible(false);
  communicationsList->setVisible(true);
  textDisplayer->setVisible(true);
  startCommunicationButton->setVisible(true);
  refreshButton->setVisible(true);
  clientsList->setVisible(true);
}
