/****************************************************************************
** Meta object code from reading C++ file 'zoneDessin.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../zoneDessin.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zoneDessin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10ZoneDessinE_t {};
} // unnamed namespace

template <> constexpr inline auto ZoneDessin::qt_create_metaobjectdata<qt_meta_tag_ZN10ZoneDessinE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ZoneDessin",
        "sommetAjouteSignal",
        "",
        "id",
        "nom",
        "QPoint",
        "pos",
        "arcCliqueSignal",
        "index",
        "arcDeselectionneSignal",
        "arcModifieSignal",
        "idDep",
        "idArr",
        "ancienPoids",
        "nouveauPoids",
        "demanderSuppressionSommetSignal",
        "idSommet"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sommetAjouteSignal'
        QtMocHelpers::SignalData<void(int, QString, QPoint)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::QString, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'arcCliqueSignal'
        QtMocHelpers::SignalData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 },
        }}),
        // Signal 'arcDeselectionneSignal'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'arcModifieSignal'
        QtMocHelpers::SignalData<void(int, int, int, int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 11 }, { QMetaType::Int, 12 }, { QMetaType::Int, 13 }, { QMetaType::Int, 14 },
        }}),
        // Signal 'demanderSuppressionSommetSignal'
        QtMocHelpers::SignalData<void(int)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 16 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ZoneDessin, qt_meta_tag_ZN10ZoneDessinE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ZoneDessin::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ZoneDessinE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ZoneDessinE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10ZoneDessinE_t>.metaTypes,
    nullptr
} };

void ZoneDessin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ZoneDessin *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sommetAjouteSignal((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QPoint>>(_a[3]))); break;
        case 1: _t->arcCliqueSignal((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->arcDeselectionneSignal(); break;
        case 3: _t->arcModifieSignal((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4]))); break;
        case 4: _t->demanderSuppressionSommetSignal((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ZoneDessin::*)(int , QString , QPoint )>(_a, &ZoneDessin::sommetAjouteSignal, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ZoneDessin::*)(int )>(_a, &ZoneDessin::arcCliqueSignal, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ZoneDessin::*)()>(_a, &ZoneDessin::arcDeselectionneSignal, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ZoneDessin::*)(int , int , int , int )>(_a, &ZoneDessin::arcModifieSignal, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ZoneDessin::*)(int )>(_a, &ZoneDessin::demanderSuppressionSommetSignal, 4))
            return;
    }
}

const QMetaObject *ZoneDessin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZoneDessin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ZoneDessinE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ZoneDessin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ZoneDessin::sommetAjouteSignal(int _t1, QString _t2, QPoint _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2, _t3);
}

// SIGNAL 1
void ZoneDessin::arcCliqueSignal(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ZoneDessin::arcDeselectionneSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ZoneDessin::arcModifieSignal(int _t1, int _t2, int _t3, int _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 4
void ZoneDessin::demanderSuppressionSommetSignal(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
