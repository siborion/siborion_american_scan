/****************************************************************************
** Meta object code from reading C++ file 'sampletable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sampletable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sampletable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_sampletable_t {
    QByteArrayData data[23];
    char stringdata[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sampletable_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sampletable_t qt_meta_stringdata_sampletable = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 9),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 15),
QT_MOC_LITERAL(4, 39, 7),
QT_MOC_LITERAL(5, 47, 15),
QT_MOC_LITERAL(6, 63, 11),
QT_MOC_LITERAL(7, 75, 4),
QT_MOC_LITERAL(8, 80, 19),
QT_MOC_LITERAL(9, 100, 10),
QT_MOC_LITERAL(10, 111, 14),
QT_MOC_LITERAL(11, 126, 11),
QT_MOC_LITERAL(12, 138, 13),
QT_MOC_LITERAL(13, 152, 8),
QT_MOC_LITERAL(14, 161, 10),
QT_MOC_LITERAL(15, 172, 12),
QT_MOC_LITERAL(16, 185, 17),
QT_MOC_LITERAL(17, 203, 12),
QT_MOC_LITERAL(18, 216, 8),
QT_MOC_LITERAL(19, 225, 8),
QT_MOC_LITERAL(20, 234, 8),
QT_MOC_LITERAL(21, 243, 3),
QT_MOC_LITERAL(22, 247, 14)
    },
    "sampletable\0changeRow\0\0stMeasureParam*\0"
    "sendAvg\0stAverageParam*\0stopMeasure\0"
    "save\0QStandardItemModel*\0changeGlas\0"
    "clearAllSignal\0clearSample\0changeRowSlot\0"
    "curIndex\0editSample\0measureParam\0"
    "changeRegimManual\0startMeasure\0saveSlot\0"
    "loadSlot\0clearAll\0del\0changeGlasSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sampletable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       6,    0,  100,    2, 0x06 /* Public */,
       7,    2,  101,    2, 0x06 /* Public */,
       9,    0,  106,    2, 0x06 /* Public */,
      10,    0,  107,    2, 0x06 /* Public */,
      11,    0,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  109,    2, 0x0a /* Public */,
      14,    1,  112,    2, 0x0a /* Public */,
      16,    1,  115,    2, 0x0a /* Public */,
      17,    0,  118,    2, 0x0a /* Public */,
      18,    0,  119,    2, 0x0a /* Public */,
      19,    0,  120,    2, 0x0a /* Public */,
      20,    0,  121,    2, 0x0a /* Public */,
      21,    0,  122,    2, 0x0a /* Public */,
      22,    0,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,   13,
    QMetaType::Void, 0x80000000 | 3,   15,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sampletable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sampletable *_t = static_cast<sampletable *>(_o);
        switch (_id) {
        case 0: _t->changeRow((*reinterpret_cast< stMeasureParam*(*)>(_a[1]))); break;
        case 1: _t->sendAvg((*reinterpret_cast< stAverageParam*(*)>(_a[1]))); break;
        case 2: _t->stopMeasure(); break;
        case 3: _t->save((*reinterpret_cast< QStandardItemModel*(*)>(_a[1])),(*reinterpret_cast< QStandardItemModel*(*)>(_a[2]))); break;
        case 4: _t->changeGlas(); break;
        case 5: _t->clearAllSignal(); break;
        case 6: _t->clearSample(); break;
        case 7: _t->changeRowSlot((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 8: _t->editSample((*reinterpret_cast< stMeasureParam*(*)>(_a[1]))); break;
        case 9: _t->changeRegimManual((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->startMeasure(); break;
        case 11: _t->saveSlot(); break;
        case 12: _t->loadSlot(); break;
        case 13: _t->clearAll(); break;
        case 14: _t->del(); break;
        case 15: _t->changeGlasSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (sampletable::*_t)(stMeasureParam * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sampletable::changeRow)) {
                *result = 0;
            }
        }
        {
            typedef void (sampletable::*_t)(stAverageParam * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sampletable::sendAvg)) {
                *result = 1;
            }
        }
        {
            typedef void (sampletable::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sampletable::stopMeasure)) {
                *result = 2;
            }
        }
        {
            typedef void (sampletable::*_t)(QStandardItemModel * , QStandardItemModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sampletable::save)) {
                *result = 3;
            }
        }
        {
            typedef void (sampletable::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sampletable::changeGlas)) {
                *result = 4;
            }
        }
        {
            typedef void (sampletable::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sampletable::clearAllSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (sampletable::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sampletable::clearSample)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject sampletable::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_sampletable.data,
      qt_meta_data_sampletable,  qt_static_metacall, 0, 0}
};


const QMetaObject *sampletable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sampletable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sampletable.stringdata))
        return static_cast<void*>(const_cast< sampletable*>(this));
    return QFrame::qt_metacast(_clname);
}

int sampletable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void sampletable::changeRow(stMeasureParam * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sampletable::sendAvg(stAverageParam * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void sampletable::stopMeasure()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void sampletable::save(QStandardItemModel * _t1, QStandardItemModel * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void sampletable::changeGlas()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void sampletable::clearAllSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void sampletable::clearSample()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
