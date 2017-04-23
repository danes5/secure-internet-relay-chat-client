//
// Created by roman on 27.2.2017.
//


#include "securityfunctions.h"
#include <QDebug>





//pre-generated random key
unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
unsigned char iv[16] = { 14, 31, 60, 126, 81, 12, 36, 102, 57, 9, 42, 51, 111, 4, 3, 25 };


void print_hex(const unsigned char buf[], std::ostream& stream, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        stream << std::hex << std::uppercase << std::setfill('0') << std::setw(2)  << (unsigned short)buf[i] << std::nouppercase << std::dec;

}


void printHelp(){
    std::cout << "Commands: " << std::endl;
    std::cout << "encrypt <source> <destination>" << std::endl;
    std::cout << "decrypt <source> <destination>" << std::endl;
    std::cout << "hash  <source> <destination>" << std::endl;
    std::cout << "verifyhash  <source> <hash_source>" << std::endl;
}

void hashFileSHA2_512(const char* src, const char* dest){
    std::ifstream source(src, std::ios::in);
    if (! source.is_open()){
        return;
    }
    std::string buffer((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
    unsigned char out[64];
    mbedtls_sha512((const unsigned char* )buffer.c_str(), buffer.length(), out, 0);
    std::ofstream destination(dest, std::ios::out);
    if ( dest == nullptr || ! destination.is_open()){
        print_hex(out, std::cout, 64);
        return;
    }
    print_hex(out, destination, 64);
}

bool verifyHashSHA_512(const char* src, const char* hashDest){
    std::ifstream source(src, std::ios::in);
    if (! source.is_open()){
        std::cout << "invalid input file" << std::endl;
        return false;
    }

    std::string inbuffer((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
    unsigned char out[64];
    mbedtls_sha512((const unsigned char* )inbuffer.c_str(), inbuffer.length(), out, 0);
    std::ifstream hash(hashDest, std::ios::in);
    if ( ! hash.is_open()){
        std::cout << "invalid hash file" << std::endl;
        return false;
    }

    std::string outbuffer((std::istreambuf_iterator<char>(hash)), std::istreambuf_iterator<char>());

    std::stringstream hashStream;
    print_hex(out, hashStream, 64);
    bool accept = true;
    if (hashStream.str() != outbuffer){
        accept = false;
    }

    if (accept){
        std::cout << "hash of the file is identical to the provided hash" << std::endl;
        return true;
    }
    std::cout << "hash of the file is different than the provided hash" << std::endl;
    return false;

}

/*void encryptDataAES_128(unsigned char* message, size_t input_len , mbedtls_aes_context* context, unsigned char *iv, unsigned char* output){
    size_t output_len = (inbuffer.length() / 16) * 16;
    if (input_len % 16 != 0)
        output_len += 16;
    input = new unsigned char[output_len]();
    memcpy(input, message, input_len);
    output = new unsigned char[output_len]();
    unsigned char local_iv[16];
    memcpy(local_iv, iv, 16);
    mbedtls_aes_crypt_cbc(aes, MBEDTLS_AES_ENCRYPT, output_len, local_iv, input, output);
}

void decrypyDataAES_128(unsigned char *input, size_t input_len, size_t output_len, mbedtls_aes_context *context, unsigned char *iv, unsigned char *output)
{
    // if message was correctly encrypted and sent to us, then it should have length divisible by 16
    if (input_len % 16 != 0){
        return;
    }
    unsigned char local_iv[16];
    memcpy(local_iv, iv, 16);
    unsigned char* out = new unsigned char[input_len]();
    output = new unsigned char[output_len]();
    mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_DECRYPT, output_len, local_iv, input, out );
    std::copy(out, out + output_len , output);
}*/

void encryptFileAES_128(const char* src, const char* dest) {

    std::ifstream source(src, std::ios::in);
    if (!source.is_open()) {
        return;
    }
    std::string inbuffer((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
    std::ofstream destination(dest, std::ios::out);
    if (!destination.is_open()) {
        return;
    }
    mbedtls_aes_context aes;
    unsigned char *input;
    unsigned char *output;
    size_t input_len = inbuffer.length();
    size_t output_len = (inbuffer.length() / 16) * 16;
    if (input_len % 16 != 0)
        output_len += 16;
    input = new unsigned char[output_len]();

    memcpy(input, inbuffer.c_str(), input_len);
    output = new unsigned char[output_len]();

    unsigned char local_iv[16];
    memcpy(local_iv, iv, 16);

    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, output_len, local_iv, input, output);
    std::copy(output, output + output_len, std::ostreambuf_iterator<char>(destination));
}



void decryptFileAES_128(const char* src, unsigned long outputLength, const char* dest){

    std::ifstream source(src, std::ios::in);
    if (! source.is_open()){
        return;
    }
    std::string inbuffer((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
    std::ofstream destination(dest, std::ios::out);
    if (! destination.is_open()){
        return;
    }
    mbedtls_aes_context aes;

    unsigned char* input;
    unsigned char* output;

    size_t input_len = inbuffer.length();
    size_t output_len = (inbuffer.length() / 16) * 16;
    if (input_len % 16 != 0)
        output_len += 16;

    input = new unsigned char[output_len]();
    memcpy(input, inbuffer.c_str(), input_len);
    output = new unsigned char[output_len]();

    unsigned char local_iv[16];
    memcpy(local_iv, iv, 16);
    mbedtls_aes_setkey_dec( &aes, key, 128 );
    mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_DECRYPT, output_len, local_iv, input, output );
    std::copy(output, output + outputLength , std::ostreambuf_iterator<char>(destination));
}



int encryptDataGCM(const unsigned char *input, size_t input_len, mbedtls_gcm_context *context,
                        const unsigned char* unprotectedData, size_t unprotectedLength,
                        unsigned char *iv, size_t iv_len, size_t tag_len, unsigned char *tag, unsigned char* output)
{
    //output = new unsigned char[input_len]();
    unsigned char local_iv[iv_len];
    memcpy(local_iv, iv, iv_len);
    int result = mbedtls_gcm_crypt_and_tag(context, MBEDTLS_GCM_ENCRYPT, input_len,
                 local_iv, iv_len, unprotectedData, unprotectedLength, input, output,
                 tag_len, tag);
    //qDebug() << "enc tag:" << tag;
    if (result !=0)
        qDebug() << "encryption failed : " << result;
    return result;


}

int decryptDataGCM(const unsigned char *input, size_t input_len, mbedtls_gcm_context *context,
                   const unsigned char* unprotectedData, size_t unprotectedLength,
                   const unsigned char *iv, size_t iv_len, size_t tag_len, const unsigned char *tag,
                   unsigned char* output){
    //output = new unsigned char[input_len]();
    unsigned char local_iv[iv_len];
    memcpy(local_iv, iv, iv_len);

    //qDebug() << "dec tag:" << tag;
    int result = mbedtls_gcm_auth_decrypt(context, input_len,
                 local_iv, iv_len, unprotectedData, unprotectedLength, tag, tag_len, input, output);
    return result;

}
