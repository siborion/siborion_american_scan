/****************************************************************************
** Meta object code from reading C++ file 'calculator_patient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../calculator_patient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calculator_patient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_calculator_patient_t {
    QByteArrayData data[9];
    char stringdata[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_calculator_patient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_calculator_patient_t qt_meta_stringdata_calculator_patient = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 14),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 20),
QT_MOC_LITERAL(4, 56, 8),
QT_MOC_LITERAL(5, 65, 10),
QT_MOC_LITERAL(6, 76, 11),
QT_MOC_LITERAL(7, 88, 19),
QT_MOC_LITERAL(8, 108, 12)
    },
    "calculator_patient\0refreshFormula\0\0"
    "changeSideCalculator\0RefreshK\0ChangeSide\0"
    "updateParam\0refreshPatientParam\0"
    "refreshAlACD"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_calculator_patient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void calculator_patient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        calculator_patient *_t = static_cast<calculator_patient *>(_o);
        switch (_id) {
        case 0: _t->refreshFormula(); break;
        case 1: _t->changeSideCalculator(); break;
        case 2: _t->RefreshK(); break;
        case 3: _t->ChangeSide(); break;
        case 4: _t->updateParam(); break;
        case 5: _t->refreshPatientParam(); break;
        case 6: _t->refreshAlACD(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (calculator_patient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&calculator_patient::refreshFormula)) {
                *result = 0;
            }
        }
        {
            typedef void (calculator_patient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&calculator_patient::changeSideCalculator)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject calculator_patient::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_calculator_patient.data,
      qt_meta_data_calculator_patient,  qt_static_metacall, 0, 0}
};


const QMetaObject *calculator_patient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *calculator_patient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_calculator_patient.stringdata))
        return static_cast<void*>(const_cast< calculator_patient*>(this));
    return QWidget::qt_metacast(_clname);
}

int calculator_patient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void calculator_patient::refreshFormula()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void calculator_patient::changeSideCalculator()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
