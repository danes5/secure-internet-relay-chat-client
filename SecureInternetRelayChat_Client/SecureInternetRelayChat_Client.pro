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
    networktransmission.cpp \
    clientslistmodel.cpp \
    activecommunicationsmodel.cpp \
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
    gcmutils.cpp





HEADERS  += mainwindow.h \
    client.h \
    channel.h \
    clientinfo.h \
    networktransmission.h \
    clientslistmodel.h \
    activecommunicationsmodel.h \
    receivingactions.h \
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
    gcmutils.h




FORMS    += mainwindow.ui
