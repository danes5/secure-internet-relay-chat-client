#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Client *cl, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = cl;
    // connects signal from client that list of active users has changed with slot in this class which updates it
    connect(client, SIGNAL(activeClientsUpdated(QList<QString>)), this, SLOT(updateActiveClients(QList<QString>)));
    connect(ui->activeCommunicationsView,SIGNAL(clicked(const QModelIndex &)), this, SLOT(onCommunicationClicked(const QModelIndex &));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateActiveClients(QList<QString> clients )
{
    QListWidget* activeCLients = ui->activeClients;
    activeCLients->clear();
    foreach (QString s, clients){
        activeCLients->addItem(s);
    }



}

void MainWindow::onCommunicationClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        activeCommunication = index.data().toString();
        ui->activeCommunicationsView->setCurrentIndex(index);
        ui->textDisplayer->setText(texts.find(cellText));
    }
}
