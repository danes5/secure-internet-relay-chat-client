/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[34];
    char stringdata0[514];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 22), // "onActiveClientsUpdated"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "clients"
QT_MOC_LITERAL(4, 39, 24), // "onRegistrationSuccessful"
QT_MOC_LITERAL(5, 64, 20), // "onRegistrationFailed"
QT_MOC_LITERAL(6, 85, 7), // "message"
QT_MOC_LITERAL(7, 93, 23), // "onMessageReceivedSignal"
QT_MOC_LITERAL(8, 117, 4), // "text"
QT_MOC_LITERAL(9, 122, 11), // "otherClient"
QT_MOC_LITERAL(10, 134, 24), // "onChannelRequestReceived"
QT_MOC_LITERAL(11, 159, 4), // "name"
QT_MOC_LITERAL(12, 164, 15), // "onChannelActive"
QT_MOC_LITERAL(13, 180, 19), // "updateActiveClients"
QT_MOC_LITERAL(14, 200, 20), // "updatedActiveClients"
QT_MOC_LITERAL(15, 221, 24), // "sendCreateChannelRequest"
QT_MOC_LITERAL(16, 246, 27), // "receiveCreateChannelRequest"
QT_MOC_LITERAL(17, 274, 10), // "ClientInfo"
QT_MOC_LITERAL(18, 285, 6), // "clInfo"
QT_MOC_LITERAL(19, 292, 11), // "sendMessage"
QT_MOC_LITERAL(20, 304, 4), // "dest"
QT_MOC_LITERAL(21, 309, 16), // "registerToServer"
QT_MOC_LITERAL(22, 326, 18), // "incomingConnection"
QT_MOC_LITERAL(23, 345, 8), // "quintptr"
QT_MOC_LITERAL(24, 354, 16), // "socketDescriptor"
QT_MOC_LITERAL(25, 371, 15), // "messageReceived"
QT_MOC_LITERAL(26, 387, 25), // "registrationReplyReceived"
QT_MOC_LITERAL(27, 413, 6), // "result"
QT_MOC_LITERAL(28, 420, 22), // "channelRequestAccepted"
QT_MOC_LITERAL(29, 443, 22), // "channelRequestDeclined"
QT_MOC_LITERAL(30, 466, 13), // "channelActive"
QT_MOC_LITERAL(31, 480, 25), // "receiveCreateChannelReply"
QT_MOC_LITERAL(32, 506, 4), // "info"
QT_MOC_LITERAL(33, 511, 2) // "id"

    },
    "Client\0onActiveClientsUpdated\0\0clients\0"
    "onRegistrationSuccessful\0onRegistrationFailed\0"
    "message\0onMessageReceivedSignal\0text\0"
    "otherClient\0onChannelRequestReceived\0"
    "name\0onChannelActive\0updateActiveClients\0"
    "updatedActiveClients\0sendCreateChannelRequest\0"
    "receiveCreateChannelRequest\0ClientInfo\0"
    "clInfo\0sendMessage\0dest\0registerToServer\0"
    "incomingConnection\0quintptr\0"
    "socketDescriptor\0messageReceived\0"
    "registrationReplyReceived\0result\0"
    "channelRequestAccepted\0channelRequestDeclined\0"
    "channelActive\0receiveCreateChannelReply\0"
    "info\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       4,    0,  112,    2, 0x06 /* Public */,
       5,    1,  113,    2, 0x06 /* Public */,
       7,    2,  116,    2, 0x06 /* Public */,
      10,    1,  121,    2, 0x06 /* Public */,
      12,    1,  124,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  127,    2, 0x0a /* Public */,
      14,    1,  128,    2, 0x0a /* Public */,
      15,    1,  131,    2, 0x0a /* Public */,
      16,    1,  134,    2, 0x0a /* Public */,
      19,    2,  137,    2, 0x0a /* Public */,
      21,    1,  142,    2, 0x0a /* Public */,
      22,    1,  145,    2, 0x0a /* Public */,
      25,    2,  148,    2, 0x0a /* Public */,
      26,    2,  153,    2, 0x0a /* Public */,
      28,    0,  158,    2, 0x0a /* Public */,
      29,    0,  159,    2, 0x0a /* Public */,
      30,    1,  160,    2, 0x0a /* Public */,
      31,    3,  163,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonArray,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonArray,    3,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   20,    8,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Bool, QMetaType::Int,   32,   27,   33,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Client *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onActiveClientsUpdated((*reinterpret_cast< QJsonArray(*)>(_a[1]))); break;
        case 1: _t->onRegistrationSuccessful(); break;
        case 2: _t->onRegistrationFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->onMessageReceivedSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->onChannelRequestReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->onChannelActive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->updateActiveClients(); break;
        case 7: _t->updatedActiveClients((*reinterpret_cast< QJsonArray(*)>(_a[1]))); break;
        case 8: _t->sendCreateChannelRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->receiveCreateChannelRequest((*reinterpret_cast< ClientInfo(*)>(_a[1]))); break;
        case 10: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->registerToServer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->incomingConnection((*reinterpret_cast< quintptr(*)>(_a[1]))); break;
        case 13: _t->messageReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->registrationReplyReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: _t->channelRequestAccepted(); break;
        case 16: _t->channelRequestDeclined(); break;
        case 17: _t->channelActive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->receiveCreateChannelReply((*reinterpret_cast< ClientInfo(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Client::*_t)(QJsonArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::onActiveClientsUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::onRegistrationSuccessful)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::onRegistrationFailed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::onMessageReceivedSignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::onChannelRequestReceived)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::onChannelActive)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client.data,
      qt_meta_data_Client,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(const_cast< Client*>(this));
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Client::onActiveClientsUpdated(QJsonArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Client::onRegistrationSuccessful()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Client::onRegistrationFailed(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Client::onMessageReceivedSignal(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Client::onChannelRequestReceived(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Client::onChannelActive(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE