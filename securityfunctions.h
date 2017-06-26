//
// Created by roman on 27.2.2017.
//

#include "libs/aes.h"
#include "libs/cipher.h"
#include "libs/gcm.h"
#include "libs/sha512.h"
#include <cstddef>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>

#ifndef PB173_TEST_SECURITYFUNCTIONS_H
#define PB173_TEST_SECURITYFUNCTIONS_H

int encryptDataGCM(const unsigned char *input, size_t input_len,
                   mbedtls_gcm_context *context,
                   const unsigned char *unprotectedData,
                   size_t unprotectedLength, unsigned char *iv, size_t iv_len,
                   size_t tag_len, unsigned char *tag, unsigned char *output);

int decryptDataGCM(const unsigned char *input, size_t input_len,
                   mbedtls_gcm_context *context,
                   const unsigned char *unprotectedData,
                   size_t unprotectedLength, const unsigned char *iv,
                   size_t iv_len, size_t tag_len, const unsigned char *tag,
                   unsigned char *output);
#endif // PB173_TEST_SECURITYFUNCTIONS_H
