/****************************************************************************
** Meta object code from reading C++ file 'InterfaceGraphique.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../InterfaceGraphique.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InterfaceGraphique.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18InterfaceGraphiqueE_t {};
} // unnamed namespace

template <> constexpr inline auto InterfaceGraphique::qt_create_metaobjectdata<qt_meta_tag_ZN18InterfaceGraphiqueE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "InterfaceGraphique",
        "on_btnSupprimerArc_clicked",
        "",
        "on_btnModifierArc_clicked",
        "on_btnAjouterArc_clicked",
        "on_btnLancerAlgorithme_clicked",
        "surNouveauSommetAjoute",
        "id",
        "nom",
        "QPoint",
        "pos",
        "surArcSelectionne",
        "index",
        "surArcDeselectionne",
        "surArcModifie",
        "idDep",
        "idArr",
        "ancienPoids",
        "nouveauPoids",
        "surDemandeSuppressionSommet",
        "idSommet",
        "on_btnChargerFichier_clicked",
        "on_btnSauvegarderFichier_clicked",
        "on_btnSaisieClavier_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_btnSupprimerArc_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnModifierArc_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnAjouterArc_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnLancerAlgorithme_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'surNouveauSommetAjoute'
        QtMocHelpers::SlotData<void(int, QString, QPoint)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 7 }, { QMetaType::QString, 8 }, { 0x80000000 | 9, 10 },
        }}),
        // Slot 'surArcSelectionne'
        QtMocHelpers::SlotData<void(int)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Slot 'surArcDeselectionne'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'surArcModifie'
        QtMocHelpers::SlotData<void(int, int, int, int)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 15 }, { QMetaType::Int, 16 }, { QMetaType::Int, 17 }, { QMetaType::Int, 18 },
        }}),
        // Slot 'surDemandeSuppressionSommet'
        QtMocHelpers::SlotData<void(int)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 20 },
        }}),
        // Slot 'on_btnChargerFichier_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSauvegarderFichier_clicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btnSaisieClavier_clicked'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<InterfaceGraphique, qt_meta_tag_ZN18InterfaceGraphiqueE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject InterfaceGraphique::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18InterfaceGraphiqueE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18InterfaceGraphiqueE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18InterfaceGraphiqueE_t>.metaTypes,
    nullptr
} };

void InterfaceGraphique::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<InterfaceGraphique *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_btnSupprimerArc_clicked(); break;
        case 1: _t->on_btnModifierArc_clicked(); break;
        case 2: _t->on_btnAjouterArc_clicked(); break;
        case 3: _t->on_btnLancerAlgorithme_clicked(); break;
        case 4: _t->surNouveauSommetAjoute((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QPoint>>(_a[3]))); break;
        case 5: _t->surArcSelectionne((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->surArcDeselectionne(); break;
        case 7: _t->surArcModifie((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4]))); break;
        case 8: _t->surDemandeSuppressionSommet((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_btnChargerFichier_clicked(); break;
        case 10: _t->on_btnSauvegarderFichier_clicked(); break;
        case 11: _t->on_btnSaisieClavier_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *InterfaceGraphique::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InterfaceGraphique::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18InterfaceGraphiqueE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int InterfaceGraphique::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
