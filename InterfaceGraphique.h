#pragma once
#include <QMainWindow>
#include"zoneDessin.h"
#include"graphe.h"

namespace Ui {
    class FenetreGraphe; // Doit correspondre au nom dans le namespace du fichier ui_interface.h
}

class InterfaceGraphique : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterfaceGraphique(QWidget* parent = nullptr);
    void chargerGrapheDeTest(); // Déclaration de la méthode
    void synchroniserComboBoxSommets();
    ~InterfaceGraphique();
private slots:
    void on_btnSupprimerArc_clicked(); // Nouveau
    void on_btnModifierArc_clicked();   // Nouveau
    void on_btnAjouterArc_clicked();
    void surNouveauSommetAjoute(int id, QString nom, QPoint pos);
    void surArcSelectionne(int index);
    void surArcDeselectionne();
    void surArcModifie(int idDep, int idArr, int ancienPoids, int nouveauPoids);
    void surDemandeSuppressionSommet(int idSommet);


private:
    Ui::FenetreGraphe* ui;
    ZoneDessin* m_zone;
    Graphe m_graphe;
    int m_indexArcSelectionne = -1;
};