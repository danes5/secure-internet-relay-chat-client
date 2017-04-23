#include "buffer.h"

Buffer::Buffer() : lengthSet(false), length(0)
{

}

void Buffer::append(const QByteArray &a)
{
    buffer.append(a);
    if (! lengthSet){
        QByteArray b = buffer.mid(0, sizeof(quint64));
        buffer.remove(0, sizeof(quint64));
        QDataStream stream(b);
        length = *(quint64*)b.data();
        lengthSet = true;
    }


}

bool Buffer::fullMessageRead()
{
    return buffer.length() == length;

}

QByteArray Buffer::getData()
{
    return buffer;

}

void Buffer::reset()
{
    lengthSet = false;
    buffer.clear();

}
