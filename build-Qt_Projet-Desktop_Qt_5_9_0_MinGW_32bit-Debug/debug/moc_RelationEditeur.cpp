/****************************************************************************
** Meta object code from reading C++ file 'RelationEditeur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt_Projet/RelationEditeur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RelationEditeur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RelationEditeur_t {
    QByteArrayData data[8];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RelationEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RelationEditeur_t qt_meta_stringdata_RelationEditeur = {
    {
QT_MOC_LITERAL(0, 0, 15), // "RelationEditeur"
QT_MOC_LITERAL(1, 16, 9), // "addCouple"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 21), // "returnToAffichageNote"
QT_MOC_LITERAL(4, 49, 22), // "activerlistNotesDroite"
QT_MOC_LITERAL(5, 72, 22), // "activerlistNotesGauche"
QT_MOC_LITERAL(6, 95, 17), // "activerLineCouple"
QT_MOC_LITERAL(7, 113, 14) // "activerajouter"

    },
    "RelationEditeur\0addCouple\0\0"
    "returnToAffichageNote\0activerlistNotesDroite\0"
    "activerlistNotesGauche\0activerLineCouple\0"
    "activerajouter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RelationEditeur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RelationEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RelationEditeur *_t = static_cast<RelationEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addCouple(); break;
        case 1: _t->returnToAffichageNote(); break;
        case 2: _t->activerlistNotesDroite(); break;
        case 3: _t->activerlistNotesGauche(); break;
        case 4: _t->activerLineCouple(); break;
        case 5: _t->activerajouter(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject RelationEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RelationEditeur.data,
      qt_meta_data_RelationEditeur,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RelationEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RelationEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RelationEditeur.stringdata0))
        return static_cast<void*>(const_cast< RelationEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int RelationEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_RelationCreateur_t {
    QByteArrayData data[4];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RelationCreateur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RelationCreateur_t qt_meta_stringdata_RelationCreateur = {
    {
QT_MOC_LITERAL(0, 0, 16), // "RelationCreateur"
QT_MOC_LITERAL(1, 17, 10), // "activerAdd"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11) // "addRelation"

    },
    "RelationCreateur\0activerAdd\0\0addRelation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RelationCreateur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RelationCreateur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RelationCreateur *_t = static_cast<RelationCreateur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activerAdd(); break;
        case 1: _t->addRelation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject RelationCreateur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RelationCreateur.data,
      qt_meta_data_RelationCreateur,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RelationCreateur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RelationCreateur::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RelationCreateur.stringdata0))
        return static_cast<void*>(const_cast< RelationCreateur*>(this));
    return QWidget::qt_metacast(_clname);
}

int RelationCreateur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
