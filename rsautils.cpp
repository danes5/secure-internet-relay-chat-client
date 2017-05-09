#include "rsautils.h"
#include <QDebug>
#include <QDataStream>

RsaUtils::RsaUtils()
{

}


int RsaUtils::initialize(){
    int ret = 0;

    mbedtls_entropy_init( &entropy );
    mbedtls_ctr_drbg_init( &ctr_drbg );
    if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy, (const unsigned char *) pers, strlen( pers ) ) ) != 0 ) {
        //qDebug() << "Chyba init rsa seed" << ret;
        return ret;
    }

    mbedtls_rsa_init( &myKeys, MBEDTLS_RSA_PKCS_V15, 0 );
    if( ( ret = mbedtls_rsa_gen_key( &myKeys, mbedtls_ctr_drbg_random, &ctr_drbg, KEY_SIZE, EXPONENT ) ) != 0 ) {
        //qDebug() << "Chyba init rsa seed" << ret;
        return ret;
     }

    mbedtls_rsa_init( &partnerPublicKey, MBEDTLS_RSA_PKCS_V15, 0 );
}

QByteArray RsaUtils::encryptMessage(QByteArray data)
{
    unsigned char output[256];
    quint64 length = data.length();



    mbedtls_rsa_pkcs1_encrypt( &partnerPublicKey, mbedtls_ctr_drbg_random,  &ctr_drbg, MBEDTLS_RSA_PUBLIC, length, (const unsigned char *)data.constData(), output );

    QByteArray encrypted;
    QDataStream stream(&encrypted, QIODevice::ReadWrite);

    encrypted = QByteArray((const char *)output, 256);

    return encrypted;
}

QByteArray RsaUtils::decryptMessage(QByteArray data)
{
    unsigned char result[2048];
    quint64 length = data.length();

    size_t i = 256;


    mbedtls_rsa_pkcs1_decrypt( &myKeys, mbedtls_ctr_drbg_random, &ctr_drbg, MBEDTLS_RSA_PRIVATE, &i, (const unsigned char *)data.constData(), result, 2048 );


    QByteArray decrypted;
    decrypted = QByteArray((const char *)result, i);

    return decrypted;
}


QJsonDocument RsaUtils::getMyPublicKey()
{
    QJsonObject jsonObject;
    char tmp[2048];
    size_t size;
    mbedtls_mpi_write_string(&myKeys.N, 16, tmp, 2048, &size);
    jsonObject.insert("N", tmp);

    mbedtls_mpi_write_string(&myKeys.E, 16, tmp, 2048, &size);
    jsonObject.insert("E", tmp);

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc;
}

QJsonDocument RsaUtils::getPartnerPublicKey()
{
    QJsonObject jsonObject;
    char tmp[2048];
    size_t size;
    mbedtls_mpi_write_string(&partnerPublicKey.N, 16, tmp, 2048, &size);
    jsonObject.insert("N", tmp);

    mbedtls_mpi_write_string(&partnerPublicKey.E, 16, tmp, 2048, &size);
    jsonObject.insert("E", tmp);

    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc;
}

void RsaUtils::setPartnerPublicKey(QJsonDocument key)
{
    QJsonObject jsonObject = key.object();
    mbedtls_mpi_read_string(&partnerPublicKey.N,16,jsonObject.take("N").toString().toStdString().c_str());
    mbedtls_mpi_read_string(&partnerPublicKey.E,16,jsonObject.take("E").toString().toStdString().c_str());
    partnerPublicKey.len = ( mbedtls_mpi_bitlen( &partnerPublicKey.N ) + 7 ) >> 3;
}

