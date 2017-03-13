
#include <iostream>
#include <cstring>
#include "securityfunctions.h"

int main(int argc, char* argv[]) {

    if (strcmp(argv[1], "encrypt") == 0){
        if (argc == 3){
            encryptFileAES_128(argv[2]);
        }
        else{
            if (argc == 4){
                encryptFileAES_128(argv[2], argv[3]);
            }else{
                std::cout << "invalid number of arguments" << std::endl;
                printHelp();
            }
        }
        return 0;
    }

    if (strcmp(argv[1], "decrypt") == 0){
        if (argc == 4){

            decryptFileAES_128(argv[2], strtoul(argv[3], nullptr, 10));
        }
        else{
            if (argc == 5){
                decryptFileAES_128(argv[2], strtoul(argv[3], nullptr, 10), argv[4]);
            }else{
                std::cout << "invalid number of arguments" << std::endl;
                printHelp();
            }
        }
        return 0;
    }

    if (strcmp(argv[1], "hash") == 0){
        if (argc == 3){
            hashFileSHA2_512(argv[2]);
        }
        else{
            if (argc == 4){
                hashFileSHA2_512(argv[2], argv[3]);
            }else{
                std::cout << "invalid number of arguments" << std::endl;
                printHelp();
            }
        }
        return 0;
    }

    if (strcmp(argv[1], "verifyhash") == 0){
        if (argc == 4){
            verifyHashSHA_512(argv[2], argv[3]);
        }
        else{
            std::cout << "invalid number of arguments" << std::endl;
            printHelp();
        }
        return 0;
    }
}
