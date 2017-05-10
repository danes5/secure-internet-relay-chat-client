#ifndef GCMUTILS_H
#define GCMUTILS_H

#include <QObject>
#include "securityfunctions.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

struct GcmUtils
{
    GcmUtils();
    QByteArray encryptAndTag(QByteArray data);
    QJsonDocument decryptAndAuthorizeFull(QByteArray array);
    QJsonDocument decryptAndAuthorizeBody(QByteArray array, const char* tag);
    void initialize();
    int generateGcmKey();
    bool setKey(unsigned char * newKey);
    //unsigned char * getKey();

    bool gcmInitialized;
    bool hasGcmKey;

    // variables used for aes encryption and decryption
    mbedtls_gcm_context context;
    static constexpr int keyBits = 32;

    static constexpr size_t iv_len = 16;
    unsigned char iv[iv_len] = { 14, 31, 60, 126, 81, 12, 36, 102, 57, 9, 42, 51, 111, 4, 3, 25 };

    const size_t tag_len = 16;

    QString getKey();

private:
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
    unsigned char key[keyBits];
};

#endif // GCMUTILS_H
