#include "saisieSouris.h"
#include "zonedessin.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QDialogButtonBox>

SaisieSouris::SaisieSouris(QWidget* parent)
    : m_parent(parent)
{
}

void SaisieSouris::saisir(Graphe& graphe)
{
    QDialog dialogue(m_parent);
    dialogue.setWindowTitle("Saisie souris du graphe");
    dialogue.setMinimumSize(720, 560);

    QVBoxLayout* layout = new QVBoxLayout(&dialogue);
    layout->setSpacing(6);
    layout->setContentsMargins(10, 10, 10, 10);

    // Barre d'outils
    QHBoxLayout* barre = new QHBoxLayout;
    QCheckBox* checkOriente = new QCheckBox("Graphe oriente");
    checkOriente->setChecked(true);
    QCheckBox* cbStations = new QCheckBox("Avec stations-essence");
    cbStations->setChecked(false);

    QPushButton* btnSommet = new QPushButton("Sommet");
    QPushButton* btnArc = new QPushButton("Arc");
    QPushButton* btnEffacer = new QPushButton("Effacer");
    QPushButton* btnReset = new QPushButton("Reinitialiser");

    for (QPushButton* btn : { btnSommet, btnArc, btnEffacer }) {
        btn->setCheckable(true);
        btn->setStyleSheet("QPushButton {border-radius: 6px;padding-left: 12px; padding-right: 12px; padding-top: 4px; padding-bottom: 4px; border: 1px solid #cccccc; background-color: #f0f0f0;}"
            "QPushButton:checked {background-color: #4a2020; border: 1px solid #fa8989;font-weight: bold; color: white;}");
    }
    btnSommet->setChecked(true);
    btnReset->setStyleSheet("color: #f38ba8;");

    barre->addWidget(checkOriente);
    barre->addWidget(cbStations);
    barre->addSpacing(16);
    barre->addWidget(new QLabel("Outil :"));
    barre->addWidget(btnSommet);
    barre->addWidget(btnArc);
    barre->addWidget(btnEffacer);
    barre->addStretch();
    barre->addWidget(btnReset);
    layout->addLayout(barre);

    // Zone de dessin
    ZoneDessin* zone = new ZoneDessin(checkOriente->isChecked(), &dialogue);
    layout->addWidget(zone, 1);

    // Boutons Valider / Annuler
    QDialogButtonBox* boutons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    boutons->button(QDialogButtonBox::Ok)->setText("Valider");
    boutons->button(QDialogButtonBox::Cancel)->setText("Annuler");
    layout->addWidget(boutons);

    // Helper : selectionner outil
    auto selectionnerOutil = [&](QPushButton* actif) {
        for (QPushButton* btn : { btnSommet, btnArc, btnEffacer })
            btn->setChecked(btn == actif);
        };

    // --- CONNEXIONS NETTOYÉES ---

    // 1. Orientation en temps réel
    QObject::connect(checkOriente, &QCheckBox::toggled, zone, [&](bool checked) {
        zone->setOriente(checked);
        zone->update();
        });

    // 2. Outils
    QObject::connect(cbStations, &QCheckBox::toggled, zone, &ZoneDessin::setAvecStations);
    QObject::connect(btnSommet, &QPushButton::clicked, zone, [&]() { selectionnerOutil(btnSommet); zone->setMode(ZoneDessin::ModeSommet); });
    QObject::connect(btnArc, &QPushButton::clicked, zone, [&]() { selectionnerOutil(btnArc); zone->setMode(ZoneDessin::ModeArc); });
    QObject::connect(btnEffacer, &QPushButton::clicked, zone, [&]() { selectionnerOutil(btnEffacer); zone->setMode(ZoneDessin::ModeEffacer); });
    QObject::connect(btnReset, &QPushButton::clicked, zone, &ZoneDessin::reinitialiser);

    // 3. Validation UNIQUE (Création du graphe + transfert des données)
    QObject::connect(boutons, &QDialogButtonBox::accepted, &dialogue, [&]() {
        // On recrée le graphe avec la valeur choisie AVANT de confirmer
        graphe = Graphe(checkOriente->isChecked());

        // On remplit le graphe avec ce qui a été dessiné
        if (zone->confirmer(graphe))
            dialogue.accept();
        });

    QObject::connect(boutons, &QDialogButtonBox::rejected, &dialogue, &QDialog::reject);

    dialogue.exec();
}