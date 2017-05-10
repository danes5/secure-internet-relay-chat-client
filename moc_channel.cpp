/****************************************************************************
** Meta object code from reading C++ file 'channel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "channel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'channel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Channel_t {
    QByteArrayData data[12];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Channel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Channel_t qt_meta_stringdata_Channel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Channel"
QT_MOC_LITERAL(1, 8, 17), // "onMessageReceived"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "text"
QT_MOC_LITERAL(4, 32, 11), // "otherClient"
QT_MOC_LITERAL(5, 44, 15), // "onChannelActive"
QT_MOC_LITERAL(6, 60, 4), // "name"
QT_MOC_LITERAL(7, 65, 11), // "sendMessage"
QT_MOC_LITERAL(8, 77, 7), // "message"
QT_MOC_LITERAL(9, 85, 8), // "sendFile"
QT_MOC_LITERAL(10, 94, 4), // "data"
QT_MOC_LITERAL(11, 99, 9) // "readyRead"

    },
    "Channel\0onMessageReceived\0\0text\0"
    "otherClient\0onChannelActive\0name\0"
    "sendMessage\0message\0sendFile\0data\0"
    "readyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Channel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   47,    2, 0x0a /* Public */,
       9,    1,   50,    2, 0x0a /* Public */,
      11,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void,

       0        // eod
};

void Channel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Channel *_t = static_cast<Channel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onMessageReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->onChannelActive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sendFile((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->readyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Channel::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Channel::onMessageReceived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Channel::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Channel::onChannelActive)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Channel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Channel.data,
      qt_meta_data_Channel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Channel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Channel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Channel.stringdata0))
        return static_cast<void*>(const_cast< Channel*>(this));
    return QObject::qt_metacast(_clname);
}

int Channel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Channel::onMessageReceived(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Channel::onChannelActive(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
