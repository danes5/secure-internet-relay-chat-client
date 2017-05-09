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
    memcpy(output, (const char *) &length, sizeof(quint64));
    memcpy(output + sizeof(quint64), tag, tag_len);

//    for (int i =0; i < tag_len; ++i){
//        stream << tag[i];
//    }

//    for (int i =0; i < data.length(); ++i){
//        stream << output[i];
//    }
    encrypted = QByteArray((const char *)output, length + sizeof(quint64));
    //encrypted.fromRawData((const char *)output, length + sizeof(quint64));
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
    //qDebug() << "tag array decryption" << tagArray;
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
    QByteArray decryptedData = QByteArray((const char *)output, array.length());

    QJsonDocument doc = QJsonDocument::fromBinaryData(decryptedData);
    //QString type = doc.object()["type"].toString();
    return doc;
}

void GcmUtils::initialize(){
    mbedtls_gcm_init( &context );

}

bool GcmUtils::generateGcmKey(){
    mbedtls_entropy_init( &entropy );

    mbedtls_ctr_drbg_init( &ctr_drbg );
    int ret;

    char *pers = "aes generate key";

    if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
        (unsigned char *) pers, strlen( pers ) ) ) != 0 )
    {
        printf( " failed\n ! mbedtls_ctr_drbg_init returned -0x%04x\n", -ret );
        return false;
    }

    if( ( ret = mbedtls_ctr_drbg_random( &ctr_drbg, key, 32 ) ) != 0 )
    {
        printf( " failed\n ! mbedtls_ctr_drbg_random returned -0x%04x\n", -ret );
        return false;
    }
    return true;

}

void GcmUtils::setKey(unsigned char * newKey){
    memcpy(key, newKey, keyBits);
    int result = mbedtls_gcm_setkey( &context,
                                     MBEDTLS_CIPHER_ID_AES, newKey, keyBits * 8 );
    if (result != 0){
        printf( " failed\n ! mbedtls_ctr_drbg_random returned -0x%04x\n", -ret );
        return false;
    }
    return true;

    //qDebug() << "result" << result;
}

unsigned char * GcmUtils::getKey(){
    return key;
}

