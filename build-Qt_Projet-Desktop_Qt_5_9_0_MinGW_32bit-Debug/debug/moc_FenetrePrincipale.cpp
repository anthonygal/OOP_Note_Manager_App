/****************************************************************************
** Meta object code from reading C++ file 'FenetrePrincipale.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt_Projet/FenetrePrincipale.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FenetrePrincipale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FenetrePrincipale_t {
    QByteArrayData data[13];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FenetrePrincipale_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FenetrePrincipale_t qt_meta_stringdata_FenetrePrincipale = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FenetrePrincipale"
QT_MOC_LITERAL(1, 18, 12), // "editRelation"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "createRelation"
QT_MOC_LITERAL(4, 47, 13), // "updateFenetre"
QT_MOC_LITERAL(5, 61, 5), // "Note&"
QT_MOC_LITERAL(6, 67, 1), // "n"
QT_MOC_LITERAL(7, 69, 14), // "viderCorbeille"
QT_MOC_LITERAL(8, 84, 18), // "restaurerCorbeille"
QT_MOC_LITERAL(9, 103, 11), // "sauvegarder"
QT_MOC_LITERAL(10, 115, 10), // "newArticle"
QT_MOC_LITERAL(11, 126, 8), // "newTache"
QT_MOC_LITERAL(12, 135, 13) // "newMultimedia"

    },
    "FenetrePrincipale\0editRelation\0\0"
    "createRelation\0updateFenetre\0Note&\0n\0"
    "viderCorbeille\0restaurerCorbeille\0"
    "sauvegarder\0newArticle\0newTache\0"
    "newMultimedia"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FenetrePrincipale[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    1,   66,    2, 0x0a /* Public */,
       4,    0,   69,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FenetrePrincipale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FenetrePrincipale *_t = static_cast<FenetrePrincipale *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editRelation(); break;
        case 1: _t->createRelation(); break;
        case 2: _t->updateFenetre((*reinterpret_cast< Note(*)>(_a[1]))); break;
        case 3: _t->updateFenetre(); break;
        case 4: _t->viderCorbeille(); break;
        case 5: _t->restaurerCorbeille(); break;
        case 6: _t->sauvegarder(); break;
        case 7: _t->newArticle(); break;
        case 8: _t->newTache(); break;
        case 9: _t->newMultimedia(); break;
        default: ;
        }
    }
}

const QMetaObject FenetrePrincipale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FenetrePrincipale.data,
      qt_meta_data_FenetrePrincipale,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FenetrePrincipale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FenetrePrincipale::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FenetrePrincipale.stringdata0))
        return static_cast<void*>(const_cast< FenetrePrincipale*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FenetrePrincipale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
