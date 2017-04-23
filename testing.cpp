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
//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "securityfunctions.h"
#include "client.h"
#include "clientslistmodel.h"
#include "channel.h"

/*Client client;
Client client2;
QList<QString> *list = client.getActiveClients();

TEST_CASE("test Client") {
    REQUIRE(*list[0].size() == 2);

    REQUIRE(*list[0].toString() == "Johny");
    REQUIRE(*list[1].toString() == "Billy");

    REQUIRE(*list[0].toString() == "Johny");

    client.registerToServer("Munchkin");
    REQUIRE(client.registrationInfo() == true);

    //client2.registerToServer("Munchkin");
    //REQUIRE(client.registrationInfo() == false);

    //client2.registerToServer("Munchkin2");
    //REQUIRE(client.registrationInfo() == true);
}


TEST_CASE("test SendMessage") {
    REQUIRE(client.sendMessage("Johny", "wdada") == 0);
    REQUIRE(client.sendMessage("Billy", "wdada") == 0);

    REQUIRE(client.sendMessage("Error", "wdada") == 0);
}


TEST_CASE("test Channel") {
    Channel chanal();

    REQUIRE(chanal.getOtherClientName() == "Johny");
}


ClientInfo info;
info.clientName = "Munchkin";
info.clientAddress =  = QHostAddress(192.168.0.2);


TEST_CASE("test ClientInfo") {
    QJsonObject json;
    info.write(&json);

    REQUIRE(json["names"] == "Munchkin");
}

*/
// --------------------------------SECTION BASIC MBEDTLS TESTS ----------------------------------------------------------------

/*TEST_CASE("test hash", "[sha-512]") {
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


TEST_CASE("GCM"){

    const size_t tag_len = 16;
    unsigned char tag[tag_len];

    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};

    static constexpr size_t iv_len = 16;
    unsigned char iv[iv_len] = { 14, 31, 60, 126, 81, 12, 36, 102, 57, 9, 42, 51, 111, 4, 3, 25 };

    QByteArray *data = new QByteArray("This us super secret message, needs to be encrypted");
    quint64 length = data->length() + tag_len;

    unsigned char output[data->length()];


    mbedtls_gcm_context context;
    mbedtls_gcm_init( &context );
    mbedtls_gcm_setkey( &context, MBEDTLS_CIPHER_ID_AES, key, 256 );

    encryptDataGCM((const unsigned char *)data->constData(), length - tag_len, &context, nullptr, 0, iv, iv_len, tag_len, tag, output);

    QByteArray encrypted;
    QDataStream stream(&encrypted, QIODevice::ReadWrite);

    stream << length << tag << (const char *)output;

    qDebug() << "output" << encrypted;

}


// ------------------------------------------ SECTION CLIENT TESTS -----------------------------------------------------------

TEST_CASE("client encrypt message"){

    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    Channel channel;
    channel.initialize();
    channel.setkey(key);
    QString text("This us super secret message, needs to be encrypted");
    QByteArray encrypted = channel.encryptMessage(text);
    qDebug() << "encrypted:" << encrypted;
}

TEST_CASE("encrypt and decrypt message"){
    Channel channel;
    channel.initialize();
    unsigned char key[32] = { 'o', 'a', 'b', 's', 'w', 'o', 'e', 'd', 'v', 'h', 'q', 'm', 'z', 'g', 'a', 'u','y','q','g','l','5','`','1','Z','q','H','7','F','f','b','n',' '};
    channel.setkey(key);
    QString text("This us super secret message, needs to be encrypted");
    QByteArray encrypted = channel.encryptMessage(text);
    QByteArray encryptedFull = encrypted.mid(sizeof(quint64), -1);
    QDataStream stream(encrypted);
    quint64 length;
    stream >> length;
    qDebug() << "length after decrypted" << length;

    QJsonDocument decryptedMessage = channel.decrypt(encryptedFull);

    QJsonObject json = decryptedMessage.object();
    REQUIRE(json["type"] == QString("send_message"));
    REQUIRE(json["data"] == QString("This us super secret message, needs to be encrypted"));
    //qDebug() << "------------textasdasdasdkjnaksjdn" << json;

}
*/
