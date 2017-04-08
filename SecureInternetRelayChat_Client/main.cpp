#include "mainwindow.h"
#include <QApplication>
#include <QThread>

#if 0
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client;
    MainWindow w(&client);
    QThread* graphicThread = new QThread();
    client.moveToThread(graphicThread);
    graphicThread->start();
    w.show();
    return a.exec();
}
#endif
