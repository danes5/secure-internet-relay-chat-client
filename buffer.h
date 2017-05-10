#ifndef BUFFER_H
#define BUFFER_H
#include <QObject>
#include <QByteArray>
#include <QDataStream>

class Buffer
{
public:
    Buffer();
    void append(const QByteArray &a);
    bool fullMessageRead();
    QByteArray getData();
    void reset();
    quint64 getLength();

private:
    QByteArray buffer;
    quint64 length;
    bool lengthSet;
};

#endif // BUFFER_H
