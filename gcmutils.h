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
    /**
     * @brief encryptAndTag encrypts data and inserts data length and tag
     * @param data protected data
     * @return encrypted data
     */
    QByteArray encryptAndTag(QByteArray data);

    /**
     * @brief decryptAndAuthorizeFull decrypts data and checks if tag matches
     * @param array encrypted data
     * @return
     */
    QJsonDocument decryptAndAuthorizeFull(QByteArray array);
    QJsonDocument decryptAndAuthorizeBody(QByteArray array, const char* tag);

    /**
     * @brief initialize init gcm
     */
    void initialize();

    /**
     * @brief generateGcmKey generate and set get
     * @return generated key
     */
    int generateGcmKey();
    /**
     * @brief setKey sets key to value
     * @param newKey key
     * @return
     */
    bool setKey(unsigned char * newKey);

    static constexpr int keyBits = 32;



    const size_t tag_len = 16;

    QString getKey();

private:
    // variables used for aes encryption and decryption
    mbedtls_gcm_context context;

    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_entropy_context entropy;
    unsigned char key[keyBits];

    static constexpr size_t iv_len = 16;
    unsigned char iv[iv_len] = { 14, 31, 60, 126, 81, 12, 36, 102, 57, 9, 42, 51, 111, 4, 3, 25 };
};

#endif // GCMUTILS_H
