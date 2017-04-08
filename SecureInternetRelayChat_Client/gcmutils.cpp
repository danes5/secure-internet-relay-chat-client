#include "gcmutils.h"
#include <QDebug>
#include <QDataStream>

GcmUtils::GcmUtils()
{

}

QByteArray GcmUtils::encryptAndTag(QByteArray data)
{
    unsigned char tag[16];
    quint64 length = data.length();

    encryptDataGCM((const unsigned char *)data.constData(), length, &context,
                  nullptr, 0, iv, iv_len, tag_len, tag, (unsigned char *)data.data());
    //qDebug() << data;
    data.prepend((const char *)tag, tag_len);
    data.prepend(QString::number(length).toUtf8());

    return data;
}

QJsonDocument GcmUtils::decryptAndAuthorizeFull(QByteArray array){

    QByteArray tagArray = array.mid(0, tag_len);
    QByteArray body = array.mid(tag_len, -1);
    return decryptAndAuthorizeBody(body, tagArray.constData());
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
