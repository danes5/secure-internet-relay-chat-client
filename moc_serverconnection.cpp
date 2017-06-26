/****************************************************************************
** Meta object code from reading C++ file 'serverconnection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serverconnection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerConnection_t {
    QByteArrayData data[23];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerConnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerConnection_t qt_meta_stringdata_ServerConnection = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ServerConnection"
QT_MOC_LITERAL(1, 17, 19), // "onRegistrationReply"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "name"
QT_MOC_LITERAL(4, 43, 6), // "result"
QT_MOC_LITERAL(5, 50, 22), // "onUpdatedActiveClients"
QT_MOC_LITERAL(6, 73, 7), // "clients"
QT_MOC_LITERAL(7, 81, 17), // "onRequestReceived"
QT_MOC_LITERAL(8, 99, 10), // "ClientInfo"
QT_MOC_LITERAL(9, 110, 6), // "clInfo"
QT_MOC_LITERAL(10, 117, 22), // "onChannelReplyReceived"
QT_MOC_LITERAL(11, 140, 2), // "id"
QT_MOC_LITERAL(12, 143, 18), // "socketStateChanged"
QT_MOC_LITERAL(13, 162, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(14, 191, 5), // "state"
QT_MOC_LITERAL(15, 197, 11), // "socketError"
QT_MOC_LITERAL(16, 209, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(17, 238, 5), // "error"
QT_MOC_LITERAL(18, 244, 9), // "sslErrors"
QT_MOC_LITERAL(19, 254, 16), // "QList<QSslError>"
QT_MOC_LITERAL(20, 271, 6), // "errors"
QT_MOC_LITERAL(21, 278, 9), // "connected"
QT_MOC_LITERAL(22, 288, 9) // "readyRead"

    },
    "ServerConnection\0onRegistrationReply\0"
    "\0name\0result\0onUpdatedActiveClients\0"
    "clients\0onRequestReceived\0ClientInfo\0"
    "clInfo\0onChannelReplyReceived\0id\0"
    "socketStateChanged\0QAbstractSocket::SocketState\0"
    "state\0socketError\0QAbstractSocket::SocketError\0"
    "error\0sslErrors\0QList<QSslError>\0"
    "errors\0connected\0readyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerConnection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    1,   64,    2, 0x06 /* Public */,
       7,    1,   67,    2, 0x06 /* Public */,
      10,    3,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   77,    2, 0x0a /* Public */,
      15,    1,   80,    2, 0x0a /* Public */,
      18,    1,   83,    2, 0x0a /* Public */,
      21,    0,   86,    2, 0x0a /* Public */,
      22,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QJsonArray,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Bool, QMetaType::Int,    9,    4,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ServerConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServerConnection *_t = static_cast<ServerConnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onRegistrationReply((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->onUpdatedActiveClients((*reinterpret_cast< QJsonArray(*)>(_a[1]))); break;
        case 2: _t->onRequestReceived((*reinterpret_cast< ClientInfo(*)>(_a[1]))); break;
        case 3: _t->onChannelReplyReceived((*reinterpret_cast< ClientInfo(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->socketStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 5: _t->socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->sslErrors((*reinterpret_cast< QList<QSslError>(*)>(_a[1]))); break;
        case 7: _t->connected(); break;
        case 8: _t->readyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ServerConnection::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerConnection::onRegistrationReply)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ServerConnection::*_t)(QJsonArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerConnection::onUpdatedActiveClients)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ServerConnection::*_t)(ClientInfo );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerConnection::onRequestReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ServerConnection::*_t)(ClientInfo , bool , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerConnection::onChannelReplyReceived)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ServerConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerConnection.data,
      qt_meta_data_ServerConnection,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ServerConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ServerConnection.stringdata0))
        return static_cast<void*>(const_cast< ServerConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ServerConnection::onRegistrationReply(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerConnection::onUpdatedActiveClients(QJsonArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerConnection::onRequestReceived(ClientInfo _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ServerConnection::onChannelReplyReceived(ClientInfo _t1, bool _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
