#include <QCoreApplication>
//#include "Server.hpp"
#include <QDebug>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QIODevice>
#include <QByteArray>


// Tell CATCH to define its main function here
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "securityfunctions.h"
#include "client.h"
#include "clientslistmodel.h"
#include "channel.h"

// --------------------------------SECTION BASIC MBEDTLS TESTS ----------------------------------------------------------------

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

TEST_CASE("GCM encrypt and decrypt"){

    const size_t tag_len = 16;
    unsigned char tag[tag_len];

    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    unsigned char bKey[32] = { 'b', 'b', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};

    static constexpr size_t iv_len = 16;
    unsigned char iv[iv_len] = { 14, 31, 60, 126, 81, 12, 36, 102, 57, 9, 42, 51, 111, 4, 3, 25 };

    QByteArray *data = new QByteArray("This us super secret message, needs to be encrypted");
    quint64 length = data->length() + tag_len;


    //unsigned char *output;
    unsigned char *output = new unsigned char[data->length()]();

//ENCRYPT
    mbedtls_gcm_context context;
    mbedtls_gcm_init( &context );
    mbedtls_gcm_setkey( &context, MBEDTLS_CIPHER_ID_AES, key, 256 );

    int result = encryptDataGCM((const unsigned char *)data->constData(), length - tag_len, &context, nullptr, 0, iv, iv_len, tag_len, tag, output);

    REQUIRE(result == 0);

    REQUIRE(strcmp((char *)output, "\0xf9\0x62\0xb3\0xca\0x17\0x3f\0x4c\0x64\0x09\0x3b\0xd3\0x69\0xd3\0xc7\0x25\0xd3\0x01\0x7f\0xc9\0x58\0x5c\0xe1\0xac\0x4a\0x3e\0x30\0xc6\0x96\0x4a\0xfa\0x65\0x97\0x58\0x86\0x1d\0x38\0xf0\0x16\0xa7\0xf4\0x5e\0x0e\0xc6\0x71\0x3f\0xbe\0x02\0x7f\0xae\0x11\0xa0\0xff\0xff\0x7f") == 0);

    REQUIRE(strcmp((char *)tag, "\0x90\0x6b\0xb3\0x4a\0x10\0x62\0x21\0x73\0xf6\0xe0\0x36\0xd6\0x96\0x12\0x8a\0xba\0x22") == 0);


//DECRYPT with correct key
    unsigned char *outputEncrypt = new unsigned char[data->length()]();
    mbedtls_gcm_context context2;
    mbedtls_gcm_init( &context2 );
    mbedtls_gcm_setkey( &context2, MBEDTLS_CIPHER_ID_AES, key, 256 );

    result = decryptDataGCM(output, length - tag_len, &context2, nullptr, 0, iv, iv_len, tag_len, tag, outputEncrypt);

    REQUIRE(result == 0);

    REQUIRE(strcmp((char *)output, "This us super secret message, needs to be encrypted") == 0);


//DECRYPT with bad key
    mbedtls_gcm_context context3;
    mbedtls_gcm_init( &context3 );
    mbedtls_gcm_setkey( &context3, MBEDTLS_CIPHER_ID_AES, bKey, 256 );

    result = decryptDataGCM(output, length - tag_len, &context3, nullptr, 0, iv, iv_len, tag_len, tag, outputEncrypt);

    REQUIRE(result == 0);

    REQUIRE(strcmp((char *)output, "This us super secret message, needs to be encrypted") != 0);


}

// ------------------------------------------ SECTION CLIENT TESTS -----------------------------------------------------------

TEST_CASE("client RegistrationRequest"){
    QByteArray refMessage("�h��6J?DRN���V�F �,g��9YQՊ��:�}�&��J.�P�{ ����");
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    Client client;
    client.initialize();
    client.setkey(key);
    bool result;

    QByteArray message = client.encryptRegistrationRequest("Arkham");
    result = (message == refMessage);
    REQUIRE(result == true);

//different name
    QByteArray message2 = client.encryptRegistrationRequest("Arkham2");
    result = (message != message2);
    REQUIRE(result == true);


//different key
    unsigned char bKey[32] = { 'b', 'b', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    client.setkey(bKey);
    message2 = client.encryptRegistrationRequest("Arkham");
    result = (message != message2);
    REQUIRE(result == true);

}


TEST_CASE("client CreateChannelRequest"){
    QByteArray refMessage("�h��6�9YQJ?D:N���V�Z �,g��9YQՊ��:�}�&��^.�G�{�t��KeG");
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    Client client;
    client.initialize();
    client.setkey(key);
    bool result;

    QByteArray message = client.encryptCreateChannelRequest("Arkham");
    result = (message == refMessage);
    REQUIRE(result == true);

//different name
    QByteArray message2 = client.encryptCreateChannelRequest("Arkham2");
    result = (message != message2);
    REQUIRE(result == true);


//different key
    unsigned char bKey[32] = { 'b', 'b', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    client.setkey(bKey);
    message2 = client.encryptCreateChannelRequest("Arkham");
    result = (message != message2);
    REQUIRE(result == true);

}


TEST_CASE("client GetActiveClientsRequest"){
    QByteArray refMessage("\0xdc\0x68\0xb0\0xca\0x36\0x4a\0x3f\0x44\0x52\0x4e\0xa3\0x0c\0xa2\0xe7\0x56\0xb6\0x46\0x0d\0xac\0x2c\0x67\0x8f\0xc9\0x39\0x59\0x51\0xd5\0x8a\0x16\0xbf\0x0b\0xf2\0x3a\0xe2\0x09\0x7d\0xf0\0x26\0xe4\0xfa\0x52\0x2e\0xa3\0x1f\0x50\0xcc\0x7b\0x0f\0x70\0xd3\0xff\0xff\0xff\0x7f");
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    Client client;
    client.initialize();
    client.setkey(key);
    bool result;

    QByteArray message = client.encryptGetActiveClientsRequest();
    result = (message == refMessage);
    REQUIRE(result == true);

//different key
    unsigned char bKey[32] = { 'b', 'b', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    client.setkey(bKey);
    QByteArray message2 = client.encryptGetActiveClientsRequest();
    result = (message != message2);
    REQUIRE(result == true);

}

TEST_CASE("client encryptClientInfo"){
    QByteArray refMessage("\0xdc\0x68\0xb0\0xca\0x36\0x4a\0x3f\0x44\0x52\0x4e\0xa3\0x0c\0xa2\0xe7\0x56\0xb6\0x46\0x0d\0xac\0x2c\0x67\0x8f\0xc9\0x39\0x59\0x51\0xd5\0x8a\0x16\0xbf\0x0b\0xf2\0x35\0xe2\0x0d\0x74\0xed\0x26\0xee\0xf8\0x5d\0x41\0xa3\0x1f\0x50\0xcc\0x7b\0x0f\0x70\0xd3\0xff\0xff\0xff\0x7f");
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    Client client;
    client.initialize();
    client.setkey(key);
    bool result;

    QByteArray message = client.encryptClientInfo();
    result = (message == refMessage);
    REQUIRE(result == true);

//different key
    unsigned char bKey[32] = { 'b', 'b', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    client.setkey(bKey);
    QByteArray message2 = client.encryptClientInfo();
    result = (message != message2);
    REQUIRE(result == true);

}

TEST_CASE("client CreateChannelReply"){
    QByteArray refMessage("\0xdc\0x68\0xb0\0xca\0x36\0x4a\0x3f\0x44\0x52\0x4e\0xa3\0x0c\0xa2\0xe7\0x56\0xb6\0x26\0x0d\0xac\0x2c\0x67\0x8f\0xc9\0x39\0x59\0x51\0xd5\0x8a\0x16\0xbf\0x0b\0xf2\0x3a\0xe2\0x1c\0x7d\0xf5\0x26\0xe4\0xe4\0x5e\0x2e\0xa3\0x1f\0x47\0xca\0x7b\0x0f\0xdc\0x74\0xa7\0xbb\0x4b\0x65\0x47");
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    Client client;
    client.initialize();
    client.setkey(key);
    bool result;

    QByteArray message = client.encryptCreateChannelReply(true, "Arkham");
    result = (message == refMessage);
    REQUIRE(result == true);

//different parameters
    QByteArray message2 = client.encryptCreateChannelReply(true, "Arkham2");
    result = (message != message2);
    REQUIRE(result == true);

    message2 = client.encryptCreateChannelReply(false, "Arkham");
    result = (message != message2);
    REQUIRE(result == true);

    message2 = client.encryptCreateChannelReply(false, "Arkham2");
    result = (message != message2);
    REQUIRE(result == true);


//different key
    unsigned char bKey[32] = { 'b', 'b', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    client.setkey(bKey);
    message2 = client.encryptCreateChannelReply(true, "Arkham");
    result = (message != message2);
    REQUIRE(result == true);

}




// ------------------------------------------ SECTION CHANNEL TESTS -----------------------------------------------------------

TEST_CASE("encrypt message"){

    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    Channel channel;
    channel.initialize();
    channel.setkey(key);
    QString text("This us super secret message, needs to be encrypted");
    QByteArray encrypted = channel.encryptMessage(text);

    QByteArray refEncrypted("�h��6J?D\016N�\014��V�\016\r�,g��9YQՊ\026�\013�1�\035}�\035��^]�~;�{\017Ar��&");
    bool result;

    result = (encrypted == refEncrypted);
    REQUIRE(result == true);


    //different key
    unsigned char bKey[32] = { 'b', 'b', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    channel.setkey(bKey);
    QByteArray encrypted2 = channel.encryptMessage(text);

    result = (encrypted != encrypted2);
    REQUIRE(result == true);

}

TEST_CASE("encrypt and decrypt message"){
    Channel channel;
    channel.initialize();
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    channel.setkey(key);
    bool result;

    QString text("This us super secret message, needs to be encrypted");
    QByteArray encrypted = channel.encryptMessage(text);
    QByteArray encryptedFull = encrypted.mid(sizeof(quint64), -1);
    QDataStream stream(encrypted);
    quint64 length;
    stream >> length;

    QJsonObject jsonObject;
    jsonObject.insert("type", "send_message");
    jsonObject.insert("data", "This us super secret message, needs to be encrypted");
    QJsonDocument refJsonDoc(jsonObject);

    //Decrypt with correct key
    QJsonDocument decryptedMessage = channel.decrypt(encryptedFull);
    result = (decryptedMessage == refJsonDoc);
    REQUIRE(result == true);

    //Decrypt with bad key
    unsigned char bKey[32] = { 'b', 'b', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    channel.setkey(key);
    decryptedMessage = channel.decrypt(encryptedFull);
    result = (decryptedMessage != refJsonDoc);
    REQUIRE(result == true);
}




