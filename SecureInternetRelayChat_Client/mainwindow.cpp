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
    activeCommunicationsView = ui->activeCommunicationsView;
    sendMessageButton = ui->sendMessageButton;
    sendFileButton = ui->sendFileButton;
    startCommunicationButton = ui->startCommunicationsButton;
    clientsListModel.setSource(client->getActiveClients());
    communicationsListModel.setSource(& texts);
    enterNameButton = ui->enterNameButton;
    enterNameFrame = ui->enterNameFrame;
    enterNameLabel = ui->enterNameLabel;
    enterNameTextEdit = ui->enterNameEdit;
    quitButton = ui->quitButton;

    activeClientsView->setModel(&clientsListModel);
    activeCommunicationsView->setModel(&communicationsListModel);
    // connects signal from client that list of active users has changed with slot in this class which updates it
    connect(client, SIGNAL(activeClientsUpdated(const QList<QString>*)), this, SLOT(updateActiveClients(const QList<QString>*)));
    connect(ui->activeCommunicationsView,SIGNAL(clicked(const QModelIndex &)), this, SLOT(onCommunicationClicked(const QModelIndex &)));
    connect(sendMessageButton, SIGNAL(pressed()), this, SLOT(sendMessageButtonPressed()));
    connect(this, SIGNAL(forwardSendMessage(QString, QString)), client, SLOT(sendMessage(QString,QString)));
    connect(this, SIGNAL(forwardStartCommunication(QString)), client, SLOT(sendCreateChannelRequest(QString)));
    connect(enterNameButton, SIGNAL(pressed()), this, SLOT(onLoginButtonClicked()));
    connect(this, SIGNAL(forwardRegisterToServer(QString)), client, SLOT(registerToServer(QString)));
    QObject::connect(quitButton, SIGNAL(clicked()),
                     QApplication::instance(), SLOT(quit()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateActiveClients(const QList<QString>* clients )
{
    clientsListModel.setSource(clients);
}

void MainWindow::onCommunicationClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        activeCommunication = index.data().toString();
        ui->activeCommunicationsView->setCurrentIndex(index);
        ui->textDisplayer->setText(*texts.find(activeCommunication));
    }
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

void MainWindow::onStartCommunicationClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QString clientName = index.data().toString();
        emit forwardStartCommunication(clientName);
    }
}

void MainWindow::onLoginButtonClicked()
{
    QString name = enterNameTextEdit->text();
    emit forwardRegisterToServer(name);
}

void MainWindow::hideLoginUI()
{
    enterNameLabel->setVisible(false);
    enterNameButton->setVisible(false);
    enterNameFrame->setVisible(false);
    enterNameTextEdit->setVisible(false);
}
