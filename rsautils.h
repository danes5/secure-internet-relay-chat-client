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
    /**
     * @brief initialize initializes rsa
     * @return 0 if success
     */
    int initialize();

    /**
     * @brief setMyKey generates and sets client key
     * @return 0 on success
     */
    int setMyKey();

    /**
     * @brief setMyKeyFromFile sets client key from file
     * @param path
     * @return 0 if success
     */
    int setMyKeyFromFile(QString path);

    /**
     * @brief setPartnerPublicKey sets public key
     * @param key
     */
    void setPartnerPublicKey(QJsonDocument key);

    /**
     * @brief setPartnerPublicKeyFromFile loads public key from file and sets it
     * @param path
     * @return
     */
    int setPartnerPublicKeyFromFile(QString path);

    /**
     * @brief getMyPublicKey return client public key
     * @return
     */
    QJsonDocument getMyPublicKey();

    /**
     * @brief getPartnerPublicKey return partner public key
     * @return
     */
    QJsonDocument getPartnerPublicKey();

    /**
     * @brief encryptMessage encrypts message using client public key
     * @param data data to encrypt
     * @return protected data
     */
    QByteArray encryptMessage(QByteArray data);

    /**
     * @brief decryptMessage decrypt message using client private key
     * @param data encrypted data
     * @return
     */
    QByteArray decryptMessage(QByteArray data);


    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    char *pers = "asjkcbnsajhcbsjhcbash";

    mbedtls_rsa_context myKeys;
    mbedtls_rsa_context partnerPublicKey;

};

#endif // RSAUTILS_H
