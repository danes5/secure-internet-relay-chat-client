//
// Created by roman on 27.2.2017.
//




#include "securityfunctions.h"
#include "ios"

// Tell CATCH to define its main function here
#define CATCH_CONFIG_MAIN
#include "catch.hpp"




TEST_CASE("test hash", "[sha-512]") {
    std::ofstream source("./files/in", std::ios::out);
    if (! source.is_open()){
        return;
    }
    source << "akafuka";
    source.close();
    hashFileSHA2_512("./files/in", "./files/out");
    std::ifstream hash("./files/out", std::ios::in);

    std::string buffer((std::istreambuf_iterator<char>(hash)), std::istreambuf_iterator<char>());
    std::string correct = "10CFD704255F7D88EC120EA7510A80FC65B4DA3E96C4E9E3FB6822EB1D79B2220D03D5220D26AD4A87D4A7D193020BCA365BEB8264DDC6034CAF4B21A7D67164";
    REQUIRE(buffer == correct);

}

TEST_CASE("test verify hash", "[sha-512]") {
    std::ofstream source("./files/in", std::ios::out);
    if (! source.is_open()){
        return;
    }
    source << "hasknfdjkqnwnqowe156451 665a464654";
    source.close();

    std::string correct = "122A0637F04F10EF450EA16B8A9DAB0BF7CCF5EB525B1D942F66DDAD9D17C4FCCA12F45B982E3929E4D0CA950EE41C2AD621EED412ED144B7EF3A1E2842D6CCB" ;
    std::ofstream destCorrect("./files/out", std::ios::out);
    if (! destCorrect.is_open()){
        return;
    }
    destCorrect << correct;
    destCorrect.close();



    std::ofstream destIncorrect("./files/out2", std::ios::out);
    if (! destIncorrect.is_open()){
        return;
    }
    destIncorrect << "132A0637F04F10EF450EA16B8A9DAB0BF7CCF5EB525B1D942F66DDAD9D17C4FCCA12F45B982E3929E4D0CA950EE41C2AD621EED412ED144B7EF3A1E2842D6CCB" << std::ios::eofbit;
    destIncorrect.close();



    REQUIRE(verifyHashSHA_512("./files/in", "./files/out"));
    REQUIRE(! verifyHashSHA_512("./files/in", "./files/out2"));
}

TEST_CASE("test encryption","[aes-128 encryption]"){
    std::ofstream source("./files/in", std::ios::out);
    if (! source.is_open()){
        return;
    }
    source << "this is ecrypted message bla bla bla ...";
    source.close();
    encryptFileAES_128("./files/in", "./files/encrypted");
    std::ifstream destFile("./files/encrypted", std::ios::in);
    if (! destFile.is_open()){
        return;
    }
    std::string output((std::istreambuf_iterator<char>(destFile)), std::istreambuf_iterator<char>());

    std::ifstream testFile("./files/encryptedTesting", std::ios::in);
    if (! destFile.is_open()){
        return;
    }
    std::string testOutput((std::istreambuf_iterator<char>(testFile)), std::istreambuf_iterator<char>());
    REQUIRE(testOutput == output);
}


TEST_CASE("test encryption and decryption","[aes-128]"){
    std::ofstream source("./files/in", std::ios::out);
    if (! source.is_open()){
        return;
    }
    source << "this is ecrypted message bla bla bla ...";
    source.close();

    encryptFileAES_128("./files/in", "./files/encrypted");
    decryptFileAES_128("./files/encrypted", 40, "./files/decrypted");



    std::ifstream decryptedFile("./files/decrypted", std::ios::in);
    if (! decryptedFile.is_open()){
        return;
    }
    std::string decryptedText((std::istreambuf_iterator<char>(decryptedFile)), std::istreambuf_iterator<char>());

    std::ifstream sourceF("./files/in", std::ios::out);
    if (! source.is_open()){
        return;
    }
    std::string originalInput;

    REQUIRE(originalInput == decryptedText);



}

