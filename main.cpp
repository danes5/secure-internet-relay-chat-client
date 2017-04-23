#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include "serverconnection.h"

#if 1
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client;
    MainWindow w(&client);
    QThread* networkThread = new QThread();
    client.moveToThread(networkThread);
    networkThread->start();
    w.show();
    //ServerConnection connection(nullptr);
    //Client client;
    //Channel channel(QHostAddress::LocalHost, 5001, nullptr);
    //for (int i = 0; i < 10000000; ++i){    }
    //channel.sendMessage("test message");
    return a.exec();
}
#endif
