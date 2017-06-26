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
    QByteArrayData data[39];
    char stringdata0[566];
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
QT_MOC_LITERAL(13, 180, 4), // "quit"
QT_MOC_LITERAL(14, 185, 14), // "channelDeleted"
QT_MOC_LITERAL(15, 200, 6), // "client"
QT_MOC_LITERAL(16, 207, 19), // "updateActiveClients"
QT_MOC_LITERAL(17, 227, 20), // "updatedActiveClients"
QT_MOC_LITERAL(18, 248, 24), // "sendCreateChannelRequest"
QT_MOC_LITERAL(19, 273, 27), // "receiveCreateChannelRequest"
QT_MOC_LITERAL(20, 301, 10), // "ClientInfo"
QT_MOC_LITERAL(21, 312, 6), // "clInfo"
QT_MOC_LITERAL(22, 319, 11), // "sendMessage"
QT_MOC_LITERAL(23, 331, 4), // "dest"
QT_MOC_LITERAL(24, 336, 16), // "registerToServer"
QT_MOC_LITERAL(25, 353, 18), // "incomingConnection"
QT_MOC_LITERAL(26, 372, 8), // "quintptr"
QT_MOC_LITERAL(27, 381, 16), // "socketDescriptor"
QT_MOC_LITERAL(28, 398, 15), // "messageReceived"
QT_MOC_LITERAL(29, 414, 25), // "registrationReplyReceived"
QT_MOC_LITERAL(30, 440, 6), // "result"
QT_MOC_LITERAL(31, 447, 22), // "channelRequestAccepted"
QT_MOC_LITERAL(32, 470, 22), // "channelRequestDeclined"
QT_MOC_LITERAL(33, 493, 13), // "channelActive"
QT_MOC_LITERAL(34, 507, 25), // "receiveCreateChannelReply"
QT_MOC_LITERAL(35, 533, 4), // "info"
QT_MOC_LITERAL(36, 538, 2), // "id"
QT_MOC_LITERAL(37, 541, 11), // "quitPressed"
QT_MOC_LITERAL(38, 553, 12) // "leaveChannel"

    },
    "Client\0onActiveClientsUpdated\0\0clients\0"
    "onRegistrationSuccessful\0onRegistrationFailed\0"
    "message\0onMessageReceivedSignal\0text\0"
    "otherClient\0onChannelRequestReceived\0"
    "name\0onChannelActive\0quit\0channelDeleted\0"
    "client\0updateActiveClients\0"
    "updatedActiveClients\0sendCreateChannelRequest\0"
    "receiveCreateChannelRequest\0ClientInfo\0"
    "clInfo\0sendMessage\0dest\0registerToServer\0"
    "incomingConnection\0quintptr\0"
    "socketDescriptor\0messageReceived\0"
    "registrationReplyReceived\0result\0"
    "channelRequestAccepted\0channelRequestDeclined\0"
    "channelActive\0receiveCreateChannelReply\0"
    "info\0id\0quitPressed\0leaveChannel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x06 /* Public */,
       4,    0,  132,    2, 0x06 /* Public */,
       5,    1,  133,    2, 0x06 /* Public */,
       7,    2,  136,    2, 0x06 /* Public */,
      10,    1,  141,    2, 0x06 /* Public */,
      12,    1,  144,    2, 0x06 /* Public */,
      13,    0,  147,    2, 0x06 /* Public */,
      14,    1,  148,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  151,    2, 0x0a /* Public */,
      17,    1,  152,    2, 0x0a /* Public */,
      18,    1,  155,    2, 0x0a /* Public */,
      19,    1,  158,    2, 0x0a /* Public */,
      22,    2,  161,    2, 0x0a /* Public */,
      24,    1,  166,    2, 0x0a /* Public */,
      25,    1,  169,    2, 0x0a /* Public */,
      28,    2,  172,    2, 0x0a /* Public */,
      29,    2,  177,    2, 0x0a /* Public */,
      31,    0,  182,    2, 0x0a /* Public */,
      32,    0,  183,    2, 0x0a /* Public */,
      33,    1,  184,    2, 0x0a /* Public */,
      34,    3,  187,    2, 0x0a /* Public */,
      37,    0,  194,    2, 0x0a /* Public */,
      38,    1,  195,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonArray,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonArray,    3,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   23,    8,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 20, QMetaType::Bool, QMetaType::Int,   35,   30,   36,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,

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
        case 6: _t->quit(); break;
        case 7: _t->channelDeleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->updateActiveClients(); break;
        case 9: _t->updatedActiveClients((*reinterpret_cast< QJsonArray(*)>(_a[1]))); break;
        case 10: _t->sendCreateChannelRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->receiveCreateChannelRequest((*reinterpret_cast< ClientInfo(*)>(_a[1]))); break;
        case 12: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: _t->registerToServer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->incomingConnection((*reinterpret_cast< quintptr(*)>(_a[1]))); break;
        case 15: _t->messageReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->registrationReplyReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: _t->channelRequestAccepted(); break;
        case 18: _t->channelRequestDeclined(); break;
        case 19: _t->channelActive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->receiveCreateChannelReply((*reinterpret_cast< ClientInfo(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 21: _t->quitPressed(); break;
        case 22: _t->leaveChannel((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::quit)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::channelDeleted)) {
                *result = 7;
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
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
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

// SIGNAL 6
void Client::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void Client::channelDeleted(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
