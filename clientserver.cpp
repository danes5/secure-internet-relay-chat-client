#include "clientserver.h"

ClientServer::ClientServer(quintptr port, QObject *parent)
    : QTcpServer(parent) {
  qDebug() << this << "created on" << QThread::currentThread()
           << " on port: " << port;
  if (!listen(QHostAddress::Any, port)) {
    qDebug() << "could not start server";
  }
}

void ClientServer::incomingConnection(qintptr socketDescriptor) {
  qDebug() << "new connection";
  emit incomingConnectionSignal(socketDescriptor);
}
