#include "rsautils.h"
#include <QDebug>
#include <QDataStream>

rsautils::rsautils()
{

}


int rsautils::initialize(){
    int ret = 0;

    mbedtls_entropy_init( &entropy );
    mbedtls_ctr_drbg_init( &ctr_drbg );
    if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy, (const unsigned char *) pers, strlen( pers ) ) ) != 0 ) {
        //qDebug() << "Chyba init rsa seed" << ret;
        return ret;
    }

    mbedtls_rsa_init( &context, MBEDTLS_RSA_PKCS_V15, 0 );
    if( ( ret = mbedtls_rsa_gen_key( &context, mbedtls_ctr_drbg_random, &ctr_drbg, KEY_SIZE, EXPONENT ) ) != 0 ) {
        //qDebug() << "Chyba init rsa seed" << ret;
        return ret;
     }
}

QByteArray rsautils::encryptMessage(QByteArray data)
{
    unsigned char output[256];
    quint64 length = data.length();



    mbedtls_rsa_pkcs1_encrypt( &context, mbedtls_ctr_drbg_random,  &ctr_drbg, MBEDTLS_RSA_PUBLIC, length, (const unsigned char *)data.constData(), output );

    QByteArray encrypted;
    QDataStream stream(&encrypted, QIODevice::ReadWrite);

    encrypted = QByteArray((const char *)output, 256);

    return encrypted;
}

QByteArray rsautils::decryptMessage(QByteArray data)
{
    unsigned char result[2048];
    quint64 length = data.length();

    size_t i = 256;


    mbedtls_rsa_pkcs1_decrypt( &context, mbedtls_ctr_drbg_random, &ctr_drbg, MBEDTLS_RSA_PRIVATE, &i, (const unsigned char *)data.constData(), result, 2048 );


    QByteArray encrypted;
    encrypted = QByteArray((const char *)result, i);

    return encrypted;
}

QJsonDocument rsautils::getPKey()
{
    QJsonObject jsonObject;
    char tmp[2048];
    size_t size;
    mbedtls_mpi_write_string(&context.N, 16, tmp, 2048, &size);
    jsonObject.insert("N", tmp);

    mbedtls_mpi_write_string(&context.E, 16, tmp, 2048, &size);
    jsonObject.insert("E", tmp);

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc;
}

void rsautils::setPKey(QJsonDocument key)
{
    QJsonObject jsonObject = key.object();
    mbedtls_mpi_read_string(&context.N,16,jsonObject.take("N").toString().toStdString().c_str());
    mbedtls_mpi_read_string(&context.E,16,jsonObject.take("E").toString().toStdString().c_str());

}
