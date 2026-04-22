#include "dialoguesaisieclavier.h"

DialogueSaisieClavier::DialogueSaisieClavier(Graphe& graphe, QWidget* parent)
    : QDialog(parent), m_graphe(graphe)
{
    setWindowTitle("Saisie clavier du graphe");
    setMinimumWidth(520);
    construireUI();
}

void DialogueSaisieClavier::construireUI()
{
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setSpacing(12);
    layoutPrincipal->setContentsMargins(14, 14, 14, 14);

    m_groupeParametres = construireGroupeParametres();
    layoutPrincipal->addWidget(m_groupeParametres);

    m_groupeArcs = construireGroupeArcs();
    layoutPrincipal->addWidget(m_groupeArcs);

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    m_btnValider  = new QPushButton("Valider");
    m_btnAnnuler  = new QPushButton("Annuler");
    m_btnValider->setDefault(true);
    layoutBoutons->addStretch();
    layoutBoutons->addWidget(m_btnValider);
    layoutBoutons->addWidget(m_btnAnnuler);
    layoutPrincipal->addLayout(layoutBoutons);

    connect(m_btnValider, &QPushButton::clicked, this, &DialogueSaisieClavier::surValidation);
    connect(m_btnAnnuler, &QPushButton::clicked, this, &QDialog::reject);
}

QGroupBox* DialogueSaisieClavier::construireGroupeParametres()
{
    QGroupBox* groupe = new QGroupBox("Paramètres du graphe");
    QVBoxLayout* layout = new QVBoxLayout(groupe);

    m_checkOriente = new QCheckBox("Graphe orienté");
    m_checkOriente->setChecked(m_graphe.retournerOriente());
    layout->addWidget(m_checkOriente);

    // Nombre de sommets existants
    int nbSommets = static_cast<int>(m_graphe.retournerSommets().size());
    int valeurInitiale = nbSommets > 0 ? nbSommets : 3;

    QHBoxLayout* layoutNb = new QHBoxLayout;
    layoutNb->addWidget(new QLabel("Nombre de sommets :"));
    m_spinNbSommets = new QSpinBox;
    m_spinNbSommets->setRange(1, 100);
    m_spinNbSommets->setValue(valeurInitiale);
    layoutNb->addWidget(m_spinNbSommets);
    layoutNb->addStretch();
    layout->addLayout(layoutNb);

    layout->addWidget(new QLabel("Noms des sommets :"));

    m_tableSommets = new QTableWidget(valeurInitiale, 1, groupe);
    m_tableSommets->setHorizontalHeaderLabels({"Nom"});
    m_tableSommets->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_tableSommets->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableSommets->setMaximumHeight(160);

    // Remplir avec les sommets existants ou des valeurs par défaut
    const auto& sommets = m_graphe.retournerSommets();
    for (int i = 0; i < valeurInitiale; ++i) {
        QString nom = (i < static_cast<int>(sommets.size()))
        ? QString::fromStdString(sommets[i].retournerDonnees())
        : QString("Sommet %1").arg(i + 1);
        m_tableSommets->setItem(i, 0, new QTableWidgetItem(nom));
    }

    connect(m_spinNbSommets, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &DialogueSaisieClavier::surChangementNbSommets);

    layout->addWidget(m_tableSommets);
    return groupe;
}

QGroupBox* DialogueSaisieClavier::construireGroupeArcs()
{
    QGroupBox* groupe = new QGroupBox("Arcs");
    QVBoxLayout* layout = new QVBoxLayout(groupe);

    m_tableArcs = new QTableWidget(0, 3, groupe);
    m_tableArcs->setHorizontalHeaderLabels({"ID Départ", "ID Arrivée", "Poids"});
    m_tableArcs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableArcs->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableArcs->setMinimumHeight(130);
    layout->addWidget(m_tableArcs);

    QHBoxLayout* layoutBtns = new QHBoxLayout;
    m_btnAjouterArc    = new QPushButton("+ Ajouter un arc");
    m_btnSupprimerArc  = new QPushButton("- Supprimer l'arc sélectionné");
    layoutBtns->addWidget(m_btnAjouterArc);
    layoutBtns->addWidget(m_btnSupprimerArc);
    layoutBtns->addStretch();
    layout->addLayout(layoutBtns);

    QLabel* aide = new QLabel(
        "<i>Les ID correspondent aux numéros de la colonne ID dans le tableau des sommets.</i>"
        );
    aide->setWordWrap(true);
    layout->addWidget(aide);


    connect(m_btnAjouterArc,   &QPushButton::clicked, this, &DialogueSaisieClavier::surAjoutArc);
    connect(m_btnSupprimerArc, &QPushButton::clicked, this, &DialogueSaisieClavier::surSuppressionArc);

    const auto& arcs = m_graphe.retournerArcs();
    int pas = m_graphe.retournerOriente() ? 1 : 2;
    int n   = m_spinNbSommets->value();

    for (int i = 0; i < static_cast<int>(arcs.size()); i += pas) {
        int ligne = m_tableArcs->rowCount();
        m_tableArcs->insertRow(ligne);

        QSpinBox* spinDep = new QSpinBox; spinDep->setRange(1, n);
        spinDep->setValue(arcs[i].retournerSommetDepart().retournerId());
        m_tableArcs->setCellWidget(ligne, 0, spinDep);

        QSpinBox* spinArr = new QSpinBox; spinArr->setRange(1, n);
        spinArr->setValue(arcs[i].retournerSommetArrivee().retournerId());
        m_tableArcs->setCellWidget(ligne, 1, spinArr);

        QSpinBox* spinPds = new QSpinBox; spinPds->setRange(-9999, 9999);
        spinPds->setValue(arcs[i].retournerPoids());
        m_tableArcs->setCellWidget(ligne, 2, spinPds);
    }

    return groupe;
}

void DialogueSaisieClavier::surChangementNbSommets(int n)
{
    m_tableSommets->setRowCount(n);
    for (int i = 0; i < n; ++i) {
        if (!m_tableSommets->item(i, 0)) {
            m_tableSommets->setItem(i, 0, new QTableWidgetItem(QString("Sommet %1").arg(i + 1)));
        }
    }
}

void DialogueSaisieClavier::surAjoutArc()
{
    int ligne = m_tableArcs->rowCount();
    m_tableArcs->insertRow(ligne);

    int n = m_spinNbSommets->value();
    QSpinBox* spinDepart = new QSpinBox;
    spinDepart->setRange(1, n);
    m_tableArcs->setCellWidget(ligne, 0, spinDepart);

    QSpinBox* spinArrivee = new QSpinBox;
    spinArrivee->setRange(1, n);
    spinArrivee->setValue(n > 1 ? 2 : 1);
    m_tableArcs->setCellWidget(ligne, 1, spinArrivee);

    QSpinBox* spinPoids = new QSpinBox;
    spinPoids->setRange(-9999, 9999);
    spinPoids->setValue(1);
    m_tableArcs->setCellWidget(ligne, 2, spinPoids);
}

void DialogueSaisieClavier::surSuppressionArc()
{
    int ligne = m_tableArcs->currentRow();
    if (ligne >= 0) {
        m_tableArcs->removeRow(ligne);
    } else {
        QMessageBox::information(this, "Suppression", "Veuillez sélectionner un arc à supprimer.");
    }
}

void DialogueSaisieClavier::surValidation()
{
    m_graphe.reinitialiser(m_checkOriente->isChecked());
    std::vector<Sommet> sommets;
    if (!validerSommets(sommets)) return;

    std::vector<Arc> arcs;
    if (!validerArcs(sommets, arcs)) return;

    for (const Sommet& s : sommets)
        m_graphe.ajouterSommet(s);

    for (const Arc& a : arcs)
        m_graphe.ajouterArc(a);

    QMessageBox::information(this, "Succès",
                             QString("Graphe créé avec %1 sommet(s) et %2 arc(s).")
                                 .arg(sommets.size())
                                 .arg(arcs.size()));
    accept();
}

bool DialogueSaisieClavier::validerSommets(std::vector<Sommet>& sommetsOut) const
{
    int n = m_spinNbSommets->value();
    for (int i = 0; i < n; ++i) {
        QTableWidgetItem* item = m_tableSommets->item(i, 0);
        QString nom = item ? item->text().trimmed() : "";
        if (nom.isEmpty()) {
            QMessageBox::warning(const_cast<DialogueSaisieClavier*>(this),
                                 "Erreur de saisie",
                                 QString("Le nom du sommet %1 est vide.").arg(i + 1));
            return false;
        }
        sommetsOut.emplace_back(i + 1, nom.toStdString());
    }
    return true;
}

bool DialogueSaisieClavier::validerArcs(const std::vector<Sommet>& sommets,
                                        std::vector<Arc>& arcsOut) const
{
    int n = static_cast<int>(sommets.size());
    int m = m_tableArcs->rowCount();

    std::vector<std::pair<int,int>> dejaSaisis;

    for (int i = 0; i < m; ++i) {
        QSpinBox* spinDep = qobject_cast<QSpinBox*>(m_tableArcs->cellWidget(i, 0));
        QSpinBox* spinArr = qobject_cast<QSpinBox*>(m_tableArcs->cellWidget(i, 1));
        QSpinBox* spinPds = qobject_cast<QSpinBox*>(m_tableArcs->cellWidget(i, 2));

        if (!spinDep || !spinArr || !spinPds) continue;

        int idDep = spinDep->value();
        int idArr = spinArr->value();
        int poids = spinPds->value();

        if (idDep < 1 || idDep > n || idArr < 1 || idArr > n) {
            QMessageBox::warning(const_cast<DialogueSaisieClavier*>(this),
                                 "Erreur de saisie",
                                 QString("Arc ligne %1 : identifiant de sommet invalide.").arg(i + 1));
            return false;
        }

        std::pair<int,int> paire = {idDep, idArr};
        for (const auto& existant : dejaSaisis) {
            if (existant == paire) {
                QMessageBox::warning(const_cast<DialogueSaisieClavier*>(this),
                                     "Erreur de saisie",
                                     QString("Arc ligne %1 : l'arc %2 → %3 est déjà présent.")
                                         .arg(i + 1).arg(idDep).arg(idArr));
                return false;
            }
        }
        dejaSaisis.push_back(paire);

        arcsOut.emplace_back(sommets[idDep - 1], sommets[idArr - 1], poids);
    }
    return true;
}
