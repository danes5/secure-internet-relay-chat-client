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

struct RsaUtils
{
    RsaUtils();
    int initialize();
    QByteArray encryptMessage(QByteArray data);
    QByteArray decryptMessage(QByteArray data);
    QJsonDocument getMyPublicKey();
    QJsonDocument getPartnerPublicKey();
    void setPartnerPublicKey(QJsonDocument key);

    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    char *pers = "asjkcbnsajhcbsjhcbash";

    mbedtls_rsa_context myKeys;
    mbedtls_rsa_context partnerPublicKey;

};

#endif // RSAUTILS_H
