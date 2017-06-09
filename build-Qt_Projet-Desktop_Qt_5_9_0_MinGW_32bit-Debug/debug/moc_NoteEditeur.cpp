/****************************************************************************
** Meta object code from reading C++ file 'NoteEditeur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt_Projet/NoteEditeur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NoteEditeur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NoteEditeur_t {
    QByteArrayData data[3];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoteEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoteEditeur_t qt_meta_stringdata_NoteEditeur = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NoteEditeur"
QT_MOC_LITERAL(1, 12, 15), // "enregistrerNote"
QT_MOC_LITERAL(2, 28, 0) // ""

    },
    "NoteEditeur\0enregistrerNote\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoteEditeur[] = {

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

void NoteEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoteEditeur *_t = static_cast<NoteEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enregistrerNote(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NoteEditeur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NoteEditeur.data,
      qt_meta_data_NoteEditeur,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NoteEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NoteEditeur.stringdata0))
        return static_cast<void*>(const_cast< NoteEditeur*>(this));
    return QWidget::qt_metacast(_clname);
}

int NoteEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ArticleEditeur_t {
    QByteArrayData data[3];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArticleEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArticleEditeur_t qt_meta_stringdata_ArticleEditeur = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ArticleEditeur"
QT_MOC_LITERAL(1, 15, 15), // "enregistrerNote"
QT_MOC_LITERAL(2, 31, 0) // ""

    },
    "ArticleEditeur\0enregistrerNote\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArticleEditeur[] = {

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

void ArticleEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ArticleEditeur *_t = static_cast<ArticleEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enregistrerNote(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ArticleEditeur::staticMetaObject = {
    { &NoteEditeur::staticMetaObject, qt_meta_stringdata_ArticleEditeur.data,
      qt_meta_data_ArticleEditeur,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ArticleEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArticleEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ArticleEditeur.stringdata0))
        return static_cast<void*>(const_cast< ArticleEditeur*>(this));
    return NoteEditeur::qt_metacast(_clname);
}

int ArticleEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NoteEditeur::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_TacheEditeur_t {
    QByteArrayData data[3];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TacheEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TacheEditeur_t qt_meta_stringdata_TacheEditeur = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TacheEditeur"
QT_MOC_LITERAL(1, 13, 15), // "enregistrerNote"
QT_MOC_LITERAL(2, 29, 0) // ""

    },
    "TacheEditeur\0enregistrerNote\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TacheEditeur[] = {

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

void TacheEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TacheEditeur *_t = static_cast<TacheEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enregistrerNote(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TacheEditeur::staticMetaObject = {
    { &NoteEditeur::staticMetaObject, qt_meta_stringdata_TacheEditeur.data,
      qt_meta_data_TacheEditeur,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TacheEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TacheEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TacheEditeur.stringdata0))
        return static_cast<void*>(const_cast< TacheEditeur*>(this));
    return NoteEditeur::qt_metacast(_clname);
}

int TacheEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NoteEditeur::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_MultimediaEditeur_t {
    QByteArrayData data[3];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MultimediaEditeur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MultimediaEditeur_t qt_meta_stringdata_MultimediaEditeur = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MultimediaEditeur"
QT_MOC_LITERAL(1, 18, 15), // "enregistrerNote"
QT_MOC_LITERAL(2, 34, 0) // ""

    },
    "MultimediaEditeur\0enregistrerNote\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MultimediaEditeur[] = {

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

void MultimediaEditeur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MultimediaEditeur *_t = static_cast<MultimediaEditeur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enregistrerNote(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MultimediaEditeur::staticMetaObject = {
    { &NoteEditeur::staticMetaObject, qt_meta_stringdata_MultimediaEditeur.data,
      qt_meta_data_MultimediaEditeur,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MultimediaEditeur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MultimediaEditeur::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MultimediaEditeur.stringdata0))
        return static_cast<void*>(const_cast< MultimediaEditeur*>(this));
    return NoteEditeur::qt_metacast(_clname);
}

int MultimediaEditeur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = NoteEditeur::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
