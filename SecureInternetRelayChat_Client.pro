#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T13:57:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SecureInternetRelayChat_Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    channel.cpp \
    clientinfo.cpp \
    clientslistmodel.cpp \
    testing.cpp \
    securityfunctions.cpp \
    libs/aes.c \
    libs/aesni.c \
    libs/gcm.c \
    libs/sha512.c \
    libs/cipher.c \
    libs/ccm.c \
    libs/cmac.c \
    libs/cipher_wrap.c \
    libs/arc4.c \
    libs/camellia.c \
    libs/blowfish.c \
    libs/des.c \
    libs/threading.c \
    libs/entropy_poll.c \
    libs/ctr_drbg.c \
    libs/timing.c \
    libs/havege.c \
    libs/entropy.c \
    libs/bignum.c \
    libs/ripemd160.c \
    libs/sha1.c \
    libs/sha256.c \
    libs/md2.c \
    libs/md4.c \
    libs/md5.c \
    libs/md_wrap.c \
    libs/asn1parse.c \
    libs/md.c \
    libs/oid.c \
    libs/rsa.c \
    gcmutils.cpp \
    rsautils.cpp \
    serverconnection.cpp \
    clientserver.cpp \
    buffer.cpp \
    parser.cpp \
    serverinfo.cpp





HEADERS  += mainwindow.h \
    client.h \
    channel.h \
    clientinfo.h \
    clientslistmodel.h \
    securityfunctions.h \
    libs/cipher_internal.h \
    libs/aes.h \
    libs/aesni.h \
    libs/gcm.h \
    libs/sha512.h \
    libs/check_config.h \
    libs/cipher.h \
    libs/config.h \
    libs/padlock.h \
    libs/platform.h \
    libs/platform_time.h \
    libs/target_config.h \
    catch.hpp \
    libs/ccm.h \
    libs/cmac.h \
    libs/arc4.h \
    libs/camellia.h \
    libs/blowfish.h \
    libs/des.h \
    libs/threading.h \
    libs/entropy_poll.h \
    libs/ctr_drbg.h \
    libs/timing.h \
    libs/havege.h \
    libs/entropy.h \
    libs/bignum.h \
    libs/ripemd160.h \
    libs/sha1.h \
    libs/sha256.h \
    libs/md2.h \
    libs/md4.h \
    libs/md5.h \
    libs/md_internal.h \
    libs/asn1.h \
    libs/md.h \
    libs/oid.h \
    libs/rsa.h \
    gcmutils.h \
    rsautils.h \
    serverconnection.h \
    clientserver.h \
    buffer.h \
    parser.h \
    serverinfo.h




FORMS    += mainwindow.ui
