#include "securityfunctions.h"
#include <QDebug>

int encryptDataGCM(const unsigned char *input, size_t input_len,
                   mbedtls_gcm_context *context,
                   const unsigned char *unprotectedData,
                   size_t unprotectedLength, unsigned char *iv, size_t iv_len,
                   size_t tag_len, unsigned char *tag, unsigned char *output) {
  unsigned char local_iv[iv_len];
  memcpy(local_iv, iv, iv_len);
  int result = mbedtls_gcm_crypt_and_tag(
      context, MBEDTLS_GCM_ENCRYPT, input_len, local_iv, iv_len,
      unprotectedData, unprotectedLength, input, output, tag_len, tag);
  if (result != 0)
    qDebug() << "encryption failed : " << result;
  return result;
}

int decryptDataGCM(const unsigned char *input, size_t input_len,
                   mbedtls_gcm_context *context,
                   const unsigned char *unprotectedData,
                   size_t unprotectedLength, const unsigned char *iv,
                   size_t iv_len, size_t tag_len, const unsigned char *tag,
                   unsigned char *output) {
  unsigned char local_iv[iv_len];
  memcpy(local_iv, iv, iv_len);
  int result = mbedtls_gcm_auth_decrypt(context, input_len, local_iv, iv_len,
                                        unprotectedData, unprotectedLength, tag,
                                        tag_len, input, output);
  return result;
}
