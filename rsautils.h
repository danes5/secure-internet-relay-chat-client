#ifndef RSAUTILS_H
#define RSAUTILS_H

#include "libs/entropy.h"
#include "libs/ctr_drbg.h"
#include "libs/rsa.h"
#include <QObject>
#include "securityfunctions.h"
#include <QJsonDocument>
#include <QJsonObject>

#define KEY_SIZE 2048
#define EXPONENT 65537
#define ERR_OPEN_FILE 1
#define ERR_READ_FILE 1

struct rsautils
{
    rsautils();
    int initialize();

    int setMyKey();
    int setMyKeyFromFile(QString path);
    void setPartnerPublicKey(QJsonDocument key);
    int setPartnerPublicKeyFromFile(QString path);

    QJsonDocument getMyPublicKey();
    QJsonDocument getPartnerPublicKey();

    QByteArray encryptMessage(QByteArray data);
    QByteArray decryptMessage(QByteArray data);


    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    char *pers = "asjkcbnsajhcbsjhcbash";

    mbedtls_rsa_context myKeys;
    mbedtls_rsa_context partnerPublicKey;

};

#endif // RSAUTILS_H
