/****************************************************************************
** Meta object code from reading C++ file 'QNotes.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt_Projet/QNotes.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QNotes.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QNoteReduite_t {
    QByteArrayData data[3];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QNoteReduite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QNoteReduite_t qt_meta_stringdata_QNoteReduite = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QNoteReduite"
QT_MOC_LITERAL(1, 13, 9), // "onClicked"
QT_MOC_LITERAL(2, 23, 0) // ""

    },
    "QNoteReduite\0onClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QNoteReduite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void QNoteReduite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QNoteReduite *_t = static_cast<QNoteReduite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QNoteReduite::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_QNoteReduite.data,
      qt_meta_data_QNoteReduite,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QNoteReduite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QNoteReduite::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QNoteReduite.stringdata0))
        return static_cast<void*>(const_cast< QNoteReduite*>(this));
    return QPushButton::qt_metacast(_clname);
}

int QNoteReduite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_QNote_t {
    QByteArrayData data[9];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QNote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QNote_t qt_meta_stringdata_QNote = {
    {
QT_MOC_LITERAL(0, 0, 5), // "QNote"
QT_MOC_LITERAL(1, 6, 6), // "editer"
QT_MOC_LITERAL(2, 13, 0), // ""
QT_MOC_LITERAL(3, 14, 9), // "supprimer"
QT_MOC_LITERAL(4, 24, 16), // "restaurerVersion"
QT_MOC_LITERAL(5, 41, 13), // "restaurerNote"
QT_MOC_LITERAL(6, 55, 14), // "tacheEnAttente"
QT_MOC_LITERAL(7, 70, 13), // "tacheTerminee"
QT_MOC_LITERAL(8, 84, 12) // "tacheReprise"

    },
    "QNote\0editer\0\0supprimer\0restaurerVersion\0"
    "restaurerNote\0tacheEnAttente\0tacheTerminee\0"
    "tacheReprise"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QNote[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QNote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QNote *_t = static_cast<QNote *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editer(); break;
        case 1: _t->supprimer(); break;
        case 2: _t->restaurerVersion(); break;
        case 3: _t->restaurerNote(); break;
        case 4: _t->tacheEnAttente(); break;
        case 5: _t->tacheTerminee(); break;
        case 6: _t->tacheReprise(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QNote::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_QNote.data,
      qt_meta_data_QNote,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QNote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QNote::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QNote.stringdata0))
        return static_cast<void*>(const_cast< QNote*>(this));
    return QFrame::qt_metacast(_clname);
}

int QNote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
