#ifndef BUFFER_H
#define BUFFER_H
#include <QObject>
#include <QByteArray>
#include <QDataStream>

class Buffer
{
public:
    Buffer();
    /**
     * @brief append append byteArray to existing buffer
     * @param a array to append
     */
    void append(const QByteArray &a);
    /**
     * @brief fullMessageRead true if whole message was read
     * @return true full, false otherwise
     */
    bool fullMessageRead();
    /**
     * @brief getData return data the buffer has read
     * @return
     */
    QByteArray getData();
    /**
     * @brief reset resets data and length
     */
    void reset();
    /**
     * @brief getLength
     * @return length of data read
     */
    quint64 getLength();

private:
    QByteArray buffer;
    quint64 length;
    bool lengthSet;
};

#endif // BUFFER_H
