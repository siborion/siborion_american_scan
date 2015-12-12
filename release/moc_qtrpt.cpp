/****************************************************************************
** Meta object code from reading C++ file 'qtrpt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtRPT/qtrpt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtrpt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtRPT_t {
    QByteArrayData data[20];
    char stringdata[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtRPT_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtRPT_t qt_meta_stringdata_QtRPT = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 8),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 5),
QT_MOC_LITERAL(4, 22, 9),
QT_MOC_LITERAL(5, 32, 9),
QT_MOC_LITERAL(6, 42, 10),
QT_MOC_LITERAL(7, 53, 10),
QT_MOC_LITERAL(8, 64, 8),
QT_MOC_LITERAL(9, 73, 15),
QT_MOC_LITERAL(10, 89, 11),
QT_MOC_LITERAL(11, 101, 13),
QT_MOC_LITERAL(12, 115, 7),
QT_MOC_LITERAL(13, 123, 15),
QT_MOC_LITERAL(14, 139, 6),
QT_MOC_LITERAL(15, 146, 5),
QT_MOC_LITERAL(16, 152, 12),
QT_MOC_LITERAL(17, 165, 9),
QT_MOC_LITERAL(18, 175, 7),
QT_MOC_LITERAL(19, 183, 8)
    },
    "QtRPT\0setValue\0\0recNo\0paramName\0"
    "QVariant&\0paramValue\0reportPage\0"
    "setField\0RptFieldObject&\0fieldObject\0"
    "setValueImage\0QImage&\0setValueDiagram\0"
    "Chart&\0chart\0printPreview\0QPrinter*\0"
    "printer\0exportTo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtRPT[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   44,    2, 0x06 /* Public */,
       8,    1,   53,    2, 0x06 /* Public */,
      11,    4,   56,    2, 0x06 /* Public */,
      13,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,   68,    2, 0x0a /* Public */,
      19,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 5, QMetaType::Int,    3,    4,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 12, QMetaType::Int,    3,    4,    6,    7,
    QMetaType::Void, 0x80000000 | 14,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,

       0        // eod
};

void QtRPT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtRPT *_t = static_cast<QtRPT *>(_o);
        switch (_id) {
        case 0: _t->setValue((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 1: _t->setField((*reinterpret_cast< RptFieldObject(*)>(_a[1]))); break;
        case 2: _t->setValueImage((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 3: _t->setValueDiagram((*reinterpret_cast< Chart(*)>(_a[1]))); break;
        case 4: _t->printPreview((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 5: _t->exportTo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtRPT::*_t)(const int , const QString , QVariant & , const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtRPT::setValue)) {
                *result = 0;
            }
        }
        {
            typedef void (QtRPT::*_t)(RptFieldObject & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtRPT::setField)) {
                *result = 1;
            }
        }
        {
            typedef void (QtRPT::*_t)(const int , const QString , QImage & , const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtRPT::setValueImage)) {
                *result = 2;
            }
        }
        {
            typedef void (QtRPT::*_t)(Chart & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtRPT::setValueDiagram)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject QtRPT::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QtRPT.data,
      qt_meta_data_QtRPT,  qt_static_metacall, 0, 0}
};


const QMetaObject *QtRPT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtRPT::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtRPT.stringdata))
        return static_cast<void*>(const_cast< QtRPT*>(this));
    return QObject::qt_metacast(_clname);
}

int QtRPT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QtRPT::setValue(const int _t1, const QString _t2, QVariant & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtRPT::setField(RptFieldObject & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtRPT::setValueImage(const int _t1, const QString _t2, QImage & _t3, const int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QtRPT::setValueDiagram(Chart & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
