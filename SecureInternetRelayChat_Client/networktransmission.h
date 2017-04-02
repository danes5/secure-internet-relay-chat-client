#ifndef NETWORKTRANSMISSION_H
#define NETWORKTRANSMISSION_H

#include <QObject>

struct NetworkTransmission
{
    NetworkTransmission();

    quint64 dataSize;
    QByteArray data;

};

#endif // NETWORKTRANSMISSION_H
