#ifndef GCMUTILS_H
#define GCMUTILS_H

#include <QObject>
#include "securityfunctions.h"
#include <QJsonDocument>
#include <QJsonObject>

struct GcmUtils
{
    GcmUtils();
    QByteArray encryptAndTag(QByteArray data);
    QJsonDocument decryptAndAuthorizeFull(QByteArray array);
    QJsonDocument decryptAndAuthorizeBody(QByteArray array, const char* tag);
    void initialize();
    unsigned char * generateGcmKey();
    void setKey(unsigned char * newKey);

    bool gcmInitialized;
    bool hasGcmKey;

    // variables used for aes encryption and decryption
    mbedtls_gcm_context context;
    static constexpr int keyBits = 32;
    unsigned char key[keyBits];
    static constexpr size_t iv_len = 16;
    unsigned char iv[iv_len] = { 14, 31, 60, 126, 81, 12, 36, 102, 57, 9, 42, 51, 111, 4, 3, 25 };

    const size_t tag_len = 16;
};

#endif // GCMUTILS_H
