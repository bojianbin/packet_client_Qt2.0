/****************************************************************************
** Meta object code from reading C++ file 'pic_show_fullscreen.h'
**
** Created: Sat Feb 15 20:46:09 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "show/pic_show_fullscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pic_show_fullscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_pic_show_fullscreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_pic_show_fullscreen[] = {
    "pic_show_fullscreen\0"
};

void pic_show_fullscreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData pic_show_fullscreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pic_show_fullscreen::staticMetaObject = {
    { &pic_show::staticMetaObject, qt_meta_stringdata_pic_show_fullscreen,
      qt_meta_data_pic_show_fullscreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pic_show_fullscreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pic_show_fullscreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pic_show_fullscreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pic_show_fullscreen))
        return static_cast<void*>(const_cast< pic_show_fullscreen*>(this));
    return pic_show::qt_metacast(_clname);
}

int pic_show_fullscreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = pic_show::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
