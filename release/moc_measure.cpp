/****************************************************************************
** Meta object code from reading C++ file 'measure.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../measure.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'measure.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Measure_t {
    QByteArrayData data[18];
    char stringdata[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Measure_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Measure_t qt_meta_stringdata_Measure = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 6),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 5),
QT_MOC_LITERAL(4, 22, 12),
QT_MOC_LITERAL(5, 35, 15),
QT_MOC_LITERAL(6, 51, 11),
QT_MOC_LITERAL(7, 63, 10),
QT_MOC_LITERAL(8, 74, 4),
QT_MOC_LITERAL(9, 79, 19),
QT_MOC_LITERAL(10, 99, 10),
QT_MOC_LITERAL(11, 110, 16),
QT_MOC_LITERAL(12, 127, 15),
QT_MOC_LITERAL(13, 143, 13),
QT_MOC_LITERAL(14, 157, 14),
QT_MOC_LITERAL(15, 172, 8),
QT_MOC_LITERAL(16, 181, 8),
QT_MOC_LITERAL(17, 190, 24)
    },
    "Measure\0doScan\0\0bool*\0refreshTable\0"
    "stMeasureParam*\0stopMeasure\0changeGlas\0"
    "save\0QStandardItemModel*\0doScanSlot\0"
    "refreshTableSlot\0stopMeasureSlot\0"
    "updatePatient\0changeGlasSlot\0saveSlot\0"
    "clearAll\0changeSideCalculatorSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Measure[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    0,   85,    2, 0x06 /* Public */,
       7,    0,   86,    2, 0x06 /* Public */,
       8,    2,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   92,    2, 0x0a /* Public */,
      11,    1,   95,    2, 0x0a /* Public */,
      12,    0,   98,    2, 0x0a /* Public */,
      13,    0,   99,    2, 0x0a /* Public */,
      14,    0,  100,    2, 0x0a /* Public */,
      15,    2,  101,    2, 0x0a /* Public */,
      16,    0,  106,    2, 0x0a /* Public */,
      17,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Measure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Measure *_t = static_cast<Measure *>(_o);
        switch (_id) {
        case 0: _t->doScan((*reinterpret_cast< bool*(*)>(_a[1]))); break;
        case 1: _t->refreshTable((*reinterpret_cast< stMeasureParam*(*)>(_a[1]))); break;
        case 2: _t->stopMeasure(); break;
        case 3: _t->changeGlas(); break;
        case 4: _t->save((*reinterpret_cast< QStandardItemModel*(*)>(_a[1])),(*reinterpret_cast< QStandardItemModel*(*)>(_a[2]))); break;
        case 5: _t->doScanSlot((*reinterpret_cast< bool*(*)>(_a[1]))); break;
        case 6: _t->refreshTableSlot((*reinterpret_cast< stMeasureParam*(*)>(_a[1]))); break;
        case 7: _t->stopMeasureSlot(); break;
        case 8: _t->updatePatient(); break;
        case 9: _t->changeGlasSlot(); break;
        case 10: _t->saveSlot((*reinterpret_cast< QStandardItemModel*(*)>(_a[1])),(*reinterpret_cast< QStandardItemModel*(*)>(_a[2]))); break;
        case 11: _t->clearAll(); break;
        case 12: _t->changeSideCalculatorSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
            }
            break;
        case 10:
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
            typedef void (Measure::*_t)(bool * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Measure::doScan)) {
                *result = 0;
            }
        }
        {
            typedef void (Measure::*_t)(stMeasureParam * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Measure::refreshTable)) {
                *result = 1;
            }
        }
        {
            typedef void (Measure::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Measure::stopMeasure)) {
                *result = 2;
            }
        }
        {
            typedef void (Measure::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Measure::changeGlas)) {
                *result = 3;
            }
        }
        {
            typedef void (Measure::*_t)(QStandardItemModel * , QStandardItemModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Measure::save)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Measure::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Measure.data,
      qt_meta_data_Measure,  qt_static_metacall, 0, 0}
};


const QMetaObject *Measure::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Measure::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Measure.stringdata))
        return static_cast<void*>(const_cast< Measure*>(this));
    return QWidget::qt_metacast(_clname);
}

int Measure::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Measure::doScan(bool * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Measure::refreshTable(stMeasureParam * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Measure::stopMeasure()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Measure::changeGlas()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Measure::save(QStandardItemModel * _t1, QStandardItemModel * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
