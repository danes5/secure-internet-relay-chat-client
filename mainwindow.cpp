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
    activeClientsView = ui->activeClientsView;
    sendMessageButton = ui->sendMessageButton;
    sendFileButton = ui->sendFileButton;
    startCommunicationButton = ui->startCommunicationsButton;
    clientsListModel.setSource(client->getActiveClients());
    enterNameButton = ui->enterNameButton;
    enterNameFrame = ui->enterNameFrame;
    enterNameLabel = ui->enterNameLabel;
    enterNameTextEdit = ui->enterNameEdit;
    quitButton = ui->quitButton;
    loginErrorLabel = ui->loginErrorLabel;
    loginErrorLabel->setVisible(false);
    communicationsList = ui->communicationsWidget;

    activeClientsView->setModel(&clientsListModel);
    // connects signal from client that list of active users has changed with slot in this class which updates it
    connect(client, SIGNAL(activeClientsUpdated(const QList<QString>*)), this, SLOT(updateActiveClients(const QList<QString>*)));
    //connect(activeCommunicationsView,SIGNAL(clicked(const QModelIndex &)), this, SLOT(onCommunicationClicked(const QModelIndex &)));
    connect(communicationsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onCommunicationClicked(QListWidgetItem*)));


    connect(activeClientsView,SIGNAL(clicked(const QModelIndex &)), this, SLOT(clientClicked(const QModelIndex &)));
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
    texts.insert("nobody", "This is a message form someone");
    texts.insert("123", "This is message from 123");
    texts.insert("roman", "message from roman: this works!");
    activeClientsView->show();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateActiveClients(const QList<QString>* clients )
{
    clientsListModel.setSource(clients);
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

void MainWindow::clientClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        selectedClient = index.data().toString();
        activeClientsView->setCurrentIndex(index);
    }
}

void MainWindow::messageReceived(QString text, QString otherClient)
{
    qDebug() << "main window message received";
    texts[otherClient].append(text);
    if (communicationsList->findItems(otherClient, Qt::MatchExactly).isEmpty())
        new QListWidgetItem(otherClient, communicationsList);



}

void MainWindow::hideLoginUI()
{
    loginErrorLabel->setVisible(false);
    enterNameLabel->setVisible(false);
    enterNameButton->setVisible(false);
    enterNameFrame->setVisible(false);
    enterNameTextEdit->setVisible(false);
}
