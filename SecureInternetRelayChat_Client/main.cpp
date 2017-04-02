#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client;
    MainWindow w(&client);
    QThread* graphicThread;
    client.moveToThread(graphicThread);
    w.show();

    return a.exec();
}
