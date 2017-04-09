#include "gcmutils.h"
#include <QDebug>
#include <QDataStream>

GcmUtils::GcmUtils()
{

}

QByteArray GcmUtils::encryptAndTag(QByteArray data)
{
    unsigned char tag[16];
    quint64 length = data.length() + tag_len;

    unsigned char output[length + sizeof(quint64)];
    encryptDataGCM((const unsigned char *)data.constData(), length - tag_len, &context,
                  nullptr, 0, iv, iv_len, tag_len, tag, output + tag_len + sizeof(quint64));
    QByteArray encrypted;
    QDataStream stream(&encrypted, QIODevice::ReadWrite);
    //qDebug() << output;

//    stream << length;
    memcpy(output, QString::number(length).constData(), sizeof(quint64));
    memcpy(output + sizeof(quint64), tag, tag_len);

//    for (int i =0; i < tag_len; ++i){
//        stream << tag[i];
//    }

//    for (int i =0; i < data.length(); ++i){
//        stream << output[i];
//    }
    encrypted.fromRawData((const char *)output, length + sizeof(quint64));
    //stream << (const char *)output;

    //data.prepend((const char *)tag, tag_len);
    //data.prepend(QString::number(length).toUtf8());

    return encrypted;
}

QJsonDocument GcmUtils::decryptAndAuthorizeFull(QByteArray array){
    const char * tagArray = array.constData();
    //QByteArray tagArray = array.mid(0, tag_len);
    //QDataStream stream(array);
    //stream >> tagArray;
    qDebug() << "tag array decryption" << tagArray;
    QByteArray body = array.mid(tag_len, -1);
    return decryptAndAuthorizeBody(body, tagArray);
}

QJsonDocument GcmUtils::decryptAndAuthorizeBody(QByteArray array, const char* tag ){
    unsigned char output[array.length()];
    int result = decryptDataGCM((const unsigned char*)array.constData(), array.length(),
                 &context, nullptr, 0, iv, iv_len,
                   tag_len, (const unsigned char* ) tag,output );
    if (result != 0){
        // this means an error during decryption
        qDebug() << "error occured during decryption" << result;
    }

    //QByteArray decryptedData((const char *)output);
    return QJsonDocument::fromRawData((const char *)output, array.length());
}

void GcmUtils::initialize(){
    mbedtls_gcm_init( &context );

}

unsigned char * GcmUtils::generateGcmKey(){
    unsigned char* newKey = new unsigned char[keyBits]();

    //qDebug() << "generate key:" << result;
    return newKey;
}

void GcmUtils::setKey(unsigned char * newKey){
    memcpy(key, newKey, keyBits);
    int result = mbedtls_gcm_setkey( &context,
                                     MBEDTLS_CIPHER_ID_AES, newKey, keyBits * 8 );
    qDebug() << "result" << result;
}
