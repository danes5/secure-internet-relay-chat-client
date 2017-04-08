#include "channel.h"
#include "QDataStream"

Channel::Channel(QObject *parent) : QObject(parent)
{
    initialize();
}

QString Channel::getOtherClientName()
{
    return otherClient.clientName;
}

QByteArray Channel::encryptMessage(QString text)
{
    QJsonObject jsonObject;
    jsonObject.insert("type", "send_message");
    jsonObject.insert("data", text);
    QJsonDocument jsonDoc(jsonObject);

    QByteArray array(jsonDoc.toBinaryData());
    return gcm.encryptAndTag(array);


/*
    // prepare additional data to send
    QByteArray protectedData;
    protectedData.append(QString::number(id));
    protectedData.append(QString("mes"));
    protectedData.append(text);

    // length will be protected data + size of tag
    length = protectedData.length() + 16;
    unprotectedData.append(QString::number(length));


    encryptDataGCM((const unsigned char *)protectedData.constData(), protectedData.length(), &context,
                  (const unsigned char *)unprotectedData.constData(), unprotectedData.length(),
                   iv, iv_len, tag_len, tag, (unsigned char *)protectedData.data());


    protectedData.append((const char *)tag, tag_len);
    protectedData.append(QString::number(length));


    return protectedData;*/
}

QJsonDocument Channel::decrypt(QByteArray array)
{
    return gcm.decryptAndAuthorizeFull(array);
}

/*QString Channel::decryptMessage(QByteArray array, const char* unprotectedData, size_t unprotectedSize, const char* tag)
{
    const unsigned char* input = (const unsigned char* )array.constData();


    // now tag has been read
    input += 16;
    size_t length = array.length() - 16;
    unsigned char output[length];
    int result = decryptDataGCM((const unsigned char*)input, length, &context, (const unsigned char *)unprotectedData, unprotectedSize, iv, iv_len,
                   tag_len, (const unsigned char* ) tag,output );
    if (result != 0){
        // this means an error during decryption
    }
    QByteArray data((const char *)output);
    QDataStream dataStream(data);
    quint64 id;
    dataStream >> id;
    QString dataType;
    dataStream >>dataType;


    QString text;
    dataStream >> text;
    return text;
}*/



void Channel::processReadyRead()
{
    QString tag;
    buffer.append(channelSocket->readAll());
    if (!receivedLength){
        if (buffer.size() >= sizeof(quint64)){
            QDataStream bufferData(buffer);
            bufferData >> expectedDataSize;
            receivedLength = true;
        }

        if (receivedLength && buffer.length() == expectedDataSize){
            //decryptMessage(buffer);
        }
    }
}

void processReceivedData(QByteArray& array){

}

void Channel::sendMessage(QString message)
{
    QByteArray m = message.toLatin1();
    channelSocket->write(m);

}

void Channel::sendFile(QByteArray data)
{

}
void Channel::initialize(){
    gcm.initialize();
}

unsigned char* Channel::generateGcmKey()
{
    return gcm.generateGcmKey();
}

void Channel::setkey(unsigned char * newKey)
{
    gcm.setKey(newKey);

}
