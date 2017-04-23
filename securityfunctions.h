//
// Created by roman on 27.2.2017.
//

#include <cstddef>
#include "libs/cipher.h"
#include "libs/aes.h"
#include "libs/sha512.h"
#include "libs/gcm.h"




#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <iomanip>

#ifndef PB173_TEST_SECURITYFUNCTIONS_H
#define PB173_TEST_SECURITYFUNCTIONS_H




void print_hex(const char *title, const unsigned char buf[], size_t len);
void printHelp();
void hashFileSHA2_512(const char* src, const char* dest = nullptr);
bool verifyHashSHA_512(const char* src, const char* hashDest);
void encryptFileAES_128(const char* src, const char* dest = nullptr);
void decryptFileAES_128(const char* src, unsigned long outputLength, const char* dest = nullptr);
void encryptDataAES_128(unsigned char* message, size_t input_len ,mbedtls_aes_context* context, unsigned char* iv, unsigned char* output);
void decrypyDataAES_128(unsigned char* input, size_t input_len, size_t output_len, mbedtls_aes_context* context, unsigned char* iv, unsigned char* output);

int encryptDataGCM(const unsigned char *input, size_t input_len, mbedtls_gcm_context *context,
                        const unsigned char* unprotectedData, size_t unprotectedLength,
                        unsigned char *iv, size_t iv_len, size_t tag_len, unsigned char *tag, unsigned char* output);

int decryptDataGCM(const unsigned char *input, size_t input_len, mbedtls_gcm_context *context,
                   const unsigned char* unprotectedData, size_t unprotectedLength,
                   const unsigned char *iv, size_t iv_len, size_t tag_len, const unsigned char *tag,
                   unsigned char* output);
#endif //PB173_TEST_SECURITYFUNCTIONS_H
