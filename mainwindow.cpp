#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(Client *cl, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = cl;
    textDisplayer = ui->textDisplayer;
    textEdit = ui->textEdit;
    sendMessageButton = ui->sendMessageButton;
    sendFileButton = ui->sendFileButton;
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



    // connects signal from client that list of active users has changed with slot in this class which updates it
    connect(client, SIGNAL(onActiveClientsUpdated(QJsonArray)), this, SLOT(updateActiveClients(QJsonArray)));
    //connect(activeCommunicationsView,SIGNAL(clicked(const QModelIndex &)), this, SLOT(onCommunicationClicked(const QModelIndex &)));
    connect(communicationsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onCommunicationClicked(QListWidgetItem*)));
    connect(clientsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(clientClicked(QListWidgetItem*)));

    //connect(activeClientsView,SIGNAL(clicked(const QModelIndex &)), this, SLOT(clientClicked(const QModelIndex &)));
    connect(sendMessageButton, SIGNAL(pressed()), this, SLOT(sendMessageButtonPressed()));
    connect(this, SIGNAL(forwardSendMessage(QString, QString)), client, SLOT(sendMessage(QString,QString)));
    connect(this, SIGNAL(forwardStartCommunication(QString)), client, SLOT(sendCreateChannelRequest(QString)));
    connect(enterNameButton, SIGNAL(pressed()), this, SLOT(onLoginButtonClicked()));
    connect(startCommunicationButton, SIGNAL(pressed()), this, SLOT(onStartCommunicationClicked()));
    connect(this, SIGNAL(forwardRegisterToServer(QString)), client, SLOT(registerToServer(QString)));
    QObject::connect(quitButton, SIGNAL(clicked()),
                     QApplication::instance(), SLOT(quit()));
    connect(client, SIGNAL(onRegistrationSuccessful()), this, SLOT(hideLoginUI()));
    connect(client, SIGNAL(onRegistrationFailed(QString)), this, SLOT(showLoginError(QString)));
    connect(client, SIGNAL(messageReceivedSignal(QString,QString)), this, SLOT(messageReceived(QString, QString)));
    connect(this, SIGNAL(onRefreshButtonPressed()), client, SLOT(updateActiveClients()));
    texts.insert("nobody", "This is a message form someone");
    texts.insert("123", "This is message from 123");
    texts.insert("roman", "message from roman: this works!");
    connect(refreshButton, SIGNAL(pressed()), this, SLOT(refreshButtonPressed()));
    connect(acceptRequestButton, SIGNAL(pressed()), this, SLOT(channelRequestAccepted()));
    connect(declineRequestButton, SIGNAL(pressed()), this, SLOT(channelRequestDeclined()));
    connect(client, SIGNAL(onChannelRequestReceived(QString)), this, SLOT(requestReceived(QString)) );
    connect(this, SIGNAL(onChannelRequestAccepted()), client, SLOT(channelRequestAccepted()));
    connect(this, SIGNAL(onChannelRequestDeclined()), client, SLOT(channelRequestDeclined()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateActiveClients(QJsonArray clients )
{
    clientsList->clear();
    for (auto cl : clients){
        new QListWidgetItem(cl.toString(), clientsList);
    }
}

void MainWindow::onCommunicationClicked(QListWidgetItem* item)
{
    qDebug() << "on communication clicked";
    activeCommunication = item->text();
    textDisplayer->setText(*texts.find(item->text()));


    /*if (index.isValid()) {
        activeCommunication = index.data().toString();
        ui->activeCommunicationsView->setCurrentIndex(index);
        ui->textDisplayer->setText(*texts.find(activeCommunication));
    }*/
}

void MainWindow::addCommunication(QString name)
{
    texts.insert(name, "");
}

void MainWindow::removeCommunication(QString name)
{
    texts.remove(name);
}

void MainWindow::sendMessageButtonPressed()
{
    QString text = textEdit->toPlainText();
    textEdit->clear();
    emit forwardSendMessage(activeCommunication, text);
}

void MainWindow::onStartCommunicationClicked()
{
        qDebug() << "start communication emmmited";
        emit forwardStartCommunication(selectedClient);
}

void MainWindow::onLoginButtonClicked()
{
    QString name = enterNameTextEdit->text();
    emit forwardRegisterToServer(name);
}

void MainWindow::showLoginError(QString message)
{
    loginErrorLabel->setText(message);
    loginErrorLabel->setVisible(true);
}

void MainWindow::clientClicked(QListWidgetItem* item)
{
    selectedClient = item->text();
}

void MainWindow::messageReceived(QString text, QString otherClient)
{
    qDebug() << "main window message received";
    texts[otherClient].append(text);
    if (communicationsList->findItems(otherClient, Qt::MatchExactly).isEmpty())
        new QListWidgetItem(otherClient, communicationsList);



}

void MainWindow::refreshButtonPressed()
{
    emit onRefreshButtonPressed();
}

void MainWindow::requestReceived(QString name)
{
    acceptRequestButton->setVisible(true);
    declineRequestButton->setVisible(true);
    requestLabel->setVisible(true);
    requestLabel->setText(QString("Received request from user: " + name));
}

void MainWindow::channelRequestAccepted()
{
    acceptRequestButton->setVisible(false);
    declineRequestButton->setVisible(false);
    requestLabel->setVisible(false);
    emit onChannelRequestAccepted();

}

void MainWindow::channelRequestDeclined()
{
    acceptRequestButton->setVisible(false);
    declineRequestButton->setVisible(false);
    requestLabel->setVisible(false);
    emit onChannelRequestDeclined();
}

void MainWindow::hideLoginUI()
{
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
