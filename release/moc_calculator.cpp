/****************************************************************************
** Meta object code from reading C++ file 'calculator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../calculator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calculator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_calculator_t {
    QByteArrayData data[18];
    char stringdata[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_calculator_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_calculator_t qt_meta_stringdata_calculator = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 20),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 24),
QT_MOC_LITERAL(4, 58, 8),
QT_MOC_LITERAL(5, 67, 5),
QT_MOC_LITERAL(6, 73, 9),
QT_MOC_LITERAL(7, 83, 9),
QT_MOC_LITERAL(8, 93, 10),
QT_MOC_LITERAL(9, 104, 10),
QT_MOC_LITERAL(10, 115, 13),
QT_MOC_LITERAL(11, 129, 7),
QT_MOC_LITERAL(12, 137, 13),
QT_MOC_LITERAL(13, 151, 14),
QT_MOC_LITERAL(14, 166, 12),
QT_MOC_LITERAL(15, 179, 11),
QT_MOC_LITERAL(16, 191, 15),
QT_MOC_LITERAL(17, 207, 4)
    },
    "calculator\0changeSideCalculator\0\0"
    "changeSideCalculatorSlot\0setValue\0"
    "recNo\0paramName\0QVariant&\0paramValue\0"
    "reportPage\0setValueImage\0QImage&\0"
    "updatePatient\0refreshFormuls\0printPreview\0"
    "refreshLens\0QSqlQueryModel*\0link"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_calculator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x08 /* Private */,
       4,    4,   56,    2, 0x08 /* Private */,
      10,    4,   65,    2, 0x08 /* Private */,
      12,    0,   74,    2, 0x0a /* Public */,
      13,    0,   75,    2, 0x0a /* Public */,
      14,    0,   76,    2, 0x0a /* Public */,
      15,    1,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 7, QMetaType::Int,    5,    6,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, 0x80000000 | 11, QMetaType::Int,    5,    6,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void calculator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        calculator *_t = static_cast<calculator *>(_o);
        switch (_id) {
        case 0: _t->changeSideCalculator(); break;
        case 1: _t->changeSideCalculatorSlot(); break;
        case 2: _t->setValue((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 3: _t->setValueImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: _t->updatePatient(); break;
        case 5: _t->refreshFormuls(); break;
        case 6: _t->printPreview(); break;
        case 7: _t->refreshLens((*reinterpret_cast< QSqlQueryModel*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSqlQueryModel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (calculator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&calculator::changeSideCalculator)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject calculator::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_calculator.data,
      qt_meta_data_calculator,  qt_static_metacall, 0, 0}
};


const QMetaObject *calculator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *calculator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_calculator.stringdata))
        return static_cast<void*>(const_cast< calculator*>(this));
    return QWidget::qt_metacast(_clname);
}

int calculator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void calculator::changeSideCalculator()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
