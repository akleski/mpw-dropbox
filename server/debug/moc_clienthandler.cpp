/****************************************************************************
** Meta object code from reading C++ file 'clienthandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../clienthandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clienthandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientHandler_t {
    QByteArrayData data[18];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientHandler_t qt_meta_stringdata_ClientHandler = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ClientHandler"
QT_MOC_LITERAL(1, 14, 5), // "error"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 23), // "QTcpSocket::SocketError"
QT_MOC_LITERAL(4, 45, 11), // "socketError"
QT_MOC_LITERAL(5, 57, 18), // "namePacketReceived"
QT_MOC_LITERAL(6, 76, 28), // "getServerFilesPacketReceived"
QT_MOC_LITERAL(7, 105, 11), // "uploadFiles"
QT_MOC_LITERAL(8, 117, 13), // "downloadFiles"
QT_MOC_LITERAL(9, 131, 11), // "processData"
QT_MOC_LITERAL(10, 143, 17), // "replyToNamePacket"
QT_MOC_LITERAL(11, 161, 21), // "replyToGetServerFiles"
QT_MOC_LITERAL(12, 183, 5), // "files"
QT_MOC_LITERAL(13, 189, 18), // "replyToUploadFiles"
QT_MOC_LITERAL(14, 208, 6), // "status"
QT_MOC_LITERAL(15, 215, 20), // "fileReadyForDownload"
QT_MOC_LITERAL(16, 236, 4), // "file"
QT_MOC_LITERAL(17, 241, 18) // "allFilesDownloaded"

    },
    "ClientHandler\0error\0\0QTcpSocket::SocketError\0"
    "socketError\0namePacketReceived\0"
    "getServerFilesPacketReceived\0uploadFiles\0"
    "downloadFiles\0processData\0replyToNamePacket\0"
    "replyToGetServerFiles\0files\0"
    "replyToUploadFiles\0status\0"
    "fileReadyForDownload\0file\0allFilesDownloaded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    2,   73,    2, 0x06 /* Public */,
       7,    3,   78,    2, 0x06 /* Public */,
       8,    3,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    1,   94,    2, 0x0a /* Public */,
      13,    1,   97,    2, 0x0a /* Public */,
      15,    1,  100,    2, 0x0a /* Public */,
      17,    0,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::QString, QMetaType::QStringList,    2,    2,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::QString, QMetaType::QStringList,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,

       0        // eod
};

void ClientHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientHandler *_t = static_cast<ClientHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QTcpSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->namePacketReceived(); break;
        case 2: _t->getServerFilesPacketReceived((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->uploadFiles((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 4: _t->downloadFiles((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 5: _t->processData(); break;
        case 6: _t->replyToNamePacket(); break;
        case 7: _t->replyToGetServerFiles((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 8: _t->replyToUploadFiles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->fileReadyForDownload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->allFilesDownloaded(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClientHandler::*_t)(QTcpSocket::SocketError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientHandler::error)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ClientHandler::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientHandler::namePacketReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ClientHandler::*_t)(qint64 , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientHandler::getServerFilesPacketReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ClientHandler::*_t)(qint64 , QString , QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientHandler::uploadFiles)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ClientHandler::*_t)(qint64 , QString , QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientHandler::downloadFiles)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject ClientHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientHandler.data,
      qt_meta_data_ClientHandler,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClientHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientHandler.stringdata0))
        return static_cast<void*>(const_cast< ClientHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int ClientHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ClientHandler::error(QTcpSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientHandler::namePacketReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ClientHandler::getServerFilesPacketReceived(qint64 _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientHandler::uploadFiles(qint64 _t1, QString _t2, QStringList _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClientHandler::downloadFiles(qint64 _t1, QString _t2, QStringList _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
