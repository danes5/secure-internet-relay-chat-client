//
// Created by roman on 27.2.2017.
//

#include <cstddef>

#ifndef PB173_TEST_SECURITYFUNCTIONS_H
#define PB173_TEST_SECURITYFUNCTIONS_H




void print_hex(const char *title, const unsigned char buf[], size_t len);
void printHelp();
void hashFileSHA2_512(const char* src, const char* dest = nullptr);
bool verifyHashSHA_512(const char* src, const char* hashDest);
void encryptFileAES_128(const char* src, const char* dest = nullptr);
void decryptFileAES_128(const char* src, unsigned long outputLength, const char* dest = nullptr);
int getInt();

#endif //PB173_TEST_SECURITYFUNCTIONS_H