#include "mainwindow.h"
#include "serverconnection.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Client client;
  MainWindow w(&client);
  QThread *networkThread = new QThread();
  QObject::connect(&w, SIGNAL(quit()), networkThread, SLOT(quit()));
  client.moveToThread(networkThread);
  networkThread->start();
  w.show();
  return a.exec();
}
