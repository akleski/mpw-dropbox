/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[17];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 16), // "nameRespReceived"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 23), // "serverFilesRespReceived"
QT_MOC_LITERAL(4, 49, 5), // "files"
QT_MOC_LITERAL(5, 55, 13), // "filesUploaded"
QT_MOC_LITERAL(6, 69, 14), // "fileDownloaded"
QT_MOC_LITERAL(7, 84, 18), // "allFilesDownloaded"
QT_MOC_LITERAL(8, 103, 18), // "localFolderChanged"
QT_MOC_LITERAL(9, 122, 3), // "dir"
QT_MOC_LITERAL(10, 126, 7), // "receive"
QT_MOC_LITERAL(11, 134, 18), // "requestServerFiles"
QT_MOC_LITERAL(12, 153, 18), // "processServerFiles"
QT_MOC_LITERAL(13, 172, 16), // "writeFileToLocal"
QT_MOC_LITERAL(14, 189, 4), // "file"
QT_MOC_LITERAL(15, 194, 15), // "startMonitoring"
QT_MOC_LITERAL(16, 210, 14) // "uploadNewFiles"

    },
    "Client\0nameRespReceived\0\0"
    "serverFilesRespReceived\0files\0"
    "filesUploaded\0fileDownloaded\0"
    "allFilesDownloaded\0localFolderChanged\0"
    "dir\0receive\0requestServerFiles\0"
    "processServerFiles\0writeFileToLocal\0"
    "file\0startMonitoring\0uploadNewFiles"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       5,    0,   78,    2, 0x06 /* Public */,
       6,    1,   79,    2, 0x06 /* Public */,
       7,    0,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   83,    2, 0x0a /* Public */,
      10,    0,   86,    2, 0x0a /* Public */,
      11,    0,   87,    2, 0x0a /* Public */,
      12,    1,   88,    2, 0x0a /* Public */,
      13,    1,   91,    2, 0x0a /* Public */,
      15,    0,   94,    2, 0x0a /* Public */,
      16,    0,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    4,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Client *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nameRespReceived(); break;
        case 1: _t->serverFilesRespReceived((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->filesUploaded(); break;
        case 3: _t->fileDownloaded((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->allFilesDownloaded(); break;
        case 5: _t->localFolderChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->receive(); break;
        case 7: _t->requestServerFiles(); break;
        case 8: _t->processServerFiles((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 9: _t->writeFileToLocal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->startMonitoring(); break;
        case 11: _t->uploadNewFiles(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::nameRespReceived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::serverFilesRespReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::filesUploaded)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::fileDownloaded)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Client::allFilesDownloaded)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client.data,
      qt_meta_data_Client,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Client::nameRespReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Client::serverFilesRespReceived(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Client::filesUploaded()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Client::fileDownloaded(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Client::allFilesDownloaded()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
