#ifndef DIALOGUESAISIECLAVIER_H
#define DIALOGUESAISIECLAVIER_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QGroupBox>
#include <QScrollArea>

#include "graphe.h"
#include "sommet.h"
#include "arc.h"

class DialogueSaisieClavier : public QDialog
{
    Q_OBJECT

public:
    explicit DialogueSaisieClavier(Graphe& graphe, QWidget* parent = nullptr);

private slots:
    void surChangementNbSommets(int n);
    void surAjoutArc();
    void surSuppressionArc();
    void surValidation();

private:
    Graphe& m_graphe;

    QGroupBox*   m_groupeParametres;
    QCheckBox*   m_checkOriente;
    QSpinBox*    m_spinNbSommets;
    QTableWidget* m_tableSommets;

    QGroupBox*    m_groupeArcs;
    QTableWidget* m_tableArcs;
    QPushButton*  m_btnAjouterArc;
    QPushButton*  m_btnSupprimerArc;

    QPushButton* m_btnValider;
    QPushButton* m_btnAnnuler;

    void construireUI();
    QGroupBox* construireGroupeParametres();
    QGroupBox* construireGroupeArcs();

    bool validerSommets(std::vector<Sommet>& sommetsOut) const;
    bool validerArcs(const std::vector<Sommet>& sommets, std::vector<Arc>& arcsOut) const;
};

#endif // DIALOGUESAISIECLAVIER_H
