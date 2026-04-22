#include "InterfaceGraphique.h"
#include "ui_interface.h"
#include "graphe.h"
#include "zonedessin.h"

InterfaceGraphique::InterfaceGraphique(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::FenetreGraphe)
{
    ui->setupUi(this);

    // 1. Mise en place de la zone de dessin manuelle
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->ongletGraphique->layout());
    layout->removeWidget(ui->zoneDessinGraphe);
    delete ui->zoneDessinGraphe;

    m_zone = new ZoneDessin(false, this);
    layout->addWidget(m_zone);

    // 2. Initialisation des données de test
    chargerGrapheDeTest();
    ui->btnSupprimerArc->setEnabled(false);
    ui->btnModifierArc->setEnabled(false);

    // 3. Mise à jour initiale des ComboBox
    synchroniserComboBoxSommets();
    //Synchroniser ajout des sommet avec list 
    connect(m_zone, &ZoneDessin::sommetAjouteSignal, this, &InterfaceGraphique::surNouveauSommetAjoute);
    // Ajoute cette ligne dans le constructeur, juste après ui->setupUi(this);
    connect(ui->btnAjouterArc, &QPushButton::clicked, this, &InterfaceGraphique::on_btnAjouterArc_clicked);
    connect(m_zone, &ZoneDessin::arcCliqueSignal, this, &InterfaceGraphique::surArcSelectionne);
    connect(m_zone, &ZoneDessin::arcDeselectionneSignal, this, &InterfaceGraphique::surArcDeselectionne);
    connect(m_zone, &ZoneDessin::arcModifieSignal, this, &InterfaceGraphique::surArcModifie);
    connect(m_zone, &ZoneDessin::demanderSuppressionSommetSignal, this, &InterfaceGraphique::surDemandeSuppressionSommet);
}

void InterfaceGraphique::chargerGrapheDeTest() {
    // On utilise directement le membre m_graphe au lieu d'une variable locale
    Sommet s1(1, "Lyon");
    Sommet s2(2, "Paris");
    Sommet s3(3, "Marseille");

    m_graphe.ajouterSommet(s1);
    m_graphe.ajouterSommet(s2);
    m_graphe.ajouterSommet(s3);

    m_graphe.ajouterArc(Arc(s1, s2, 450));
    m_graphe.ajouterArc(Arc(s2, s3, 800));
    m_graphe.ajouterArc(Arc(s3, s1, 300));

    // Mise à jour de la vue
    if (m_zone) {
        m_zone->chargerDepuisGraphe(m_graphe);
    }
}
void InterfaceGraphique::on_btnAjouterArc_clicked() {
    qDebug() << "Clic détecté sur Ajouter Arc !"; // <-- AJOUTE ÇA
    int idDep = ui->comboSommetSource->currentData().toInt();
    int idArr = ui->comboSommetDestination->currentData().toInt();
    int poids = ui->inputPoidsArc->text().toInt();

    // 1. Récupération des objets via ta méthode de recherche
    Sommet sDep = m_graphe.chercherSommetParId(idDep);
    Sommet sArr = m_graphe.chercherSommetParId(idArr);

    // 2. Utilisation de la méthode officielle de ta classe Graphe
    m_graphe.ajouterArc(Arc(sDep, sArr, poids));

    // 3. Mise à jour de la vue
    m_zone->ajouterArcDeLExterieur(idDep, idArr, poids);

    ui->inputPoidsArc->clear();
}
void InterfaceGraphique::synchroniserComboBoxSommets() {
    ui->comboSommetSource->clear();
    ui->comboSommetDestination->clear();

    // On parcourt la liste des sommets stockés dans ton modèle m_graphe
    for (const Sommet& s : m_graphe.retournerSommets()) {
        // On affiche le nom, mais on garde l'ID en "data" pour le récupérer facilement plus tard
        QString libelle = QString::fromStdString(s.retournerDonnees());
        int id = s.retournerId();

        ui->comboSommetSource->addItem(libelle, id);
        ui->comboSommetDestination->addItem(libelle, id);
    }
}
void InterfaceGraphique::surNouveauSommetAjoute(int id, QString nom, QPoint pos) {
    m_graphe.ajouterSommet(Sommet(id, nom.toStdString()));
    // Tu as maintenant accès à 'pos' ici pour tes calculs si besoin !
    synchroniserComboBoxSommets();
}
// Slot pour l'arc sélectionné
void InterfaceGraphique::surArcSelectionne(int index) {
    m_indexArcSelectionne = index;
    ui->btnSupprimerArc->setEnabled(true);
    ui->btnModifierArc->setEnabled(true);
}

// Slot pour désélectionner (quand on clique ailleurs)
void InterfaceGraphique::surArcDeselectionne() {
    m_indexArcSelectionne = -1;
    ui->btnSupprimerArc->setEnabled(false);
    ui->btnModifierArc->setEnabled(false);
}
void InterfaceGraphique::on_btnModifierArc_clicked() {
    if (m_indexArcSelectionne == -1) return;

    int poidsActuel = m_zone->getPoidsArc(m_indexArcSelectionne);
    bool ok;
    int nouveauPoids = QInputDialog::getInt(this, "Modifier l'arc",
        "Nouveau poids :", poidsActuel, -9999, 9999, 1, &ok);

    if (ok) {
        ZoneDessin::ArcVisuel av = m_zone->getArc(m_indexArcSelectionne);

        // Mise à jour modèle uniquement
        Sommet sDep = m_graphe.chercherSommetParId(av.idDepart);
        Sommet sArr = m_graphe.chercherSommetParId(av.idArrivee);
        m_graphe.supprimerArc(Arc(sDep, sArr, poidsActuel));
        m_graphe.ajouterArc(Arc(sDep, sArr, nouveauPoids));

        // Mise à jour visuel — une seule fois
        m_zone->modifierPoidsVisuel(m_indexArcSelectionne, nouveauPoids);
    }
}
void InterfaceGraphique::on_btnSupprimerArc_clicked() {
    if (m_indexArcSelectionne == -1) return;

    // 1. Récupérer les données de l'arc via l'index
    ZoneDessin::ArcVisuel av = m_zone->getArc(m_indexArcSelectionne);

    // 2. Supprimer dans le modèle (Graphe)
    // On doit reconstruire l'arc pour le supprimer
    Sommet sDep = m_graphe.chercherSommetParId(av.idDepart);
    Sommet sArr = m_graphe.chercherSommetParId(av.idArrivee);
    m_graphe.supprimerArc(Arc(sDep, sArr, av.poids));

    // 3. Supprimer dans la vue (ZoneDessin)
    m_zone->supprimerArcVisuel(m_indexArcSelectionne);

    // 4. Nettoyage
    m_indexArcSelectionne = -1;
    ui->btnSupprimerArc->setEnabled(false);
    ui->btnModifierArc->setEnabled(false);

    qDebug() << "Arc supprimé avec succès.";
}
void InterfaceGraphique::surArcModifie(int idDep, int idArr, int ancienPoids, int nouveauPoids) {
        // Mise à jour du modèle uniquement
        Sommet sDep = m_graphe.chercherSommetParId(idDep);
        Sommet sArr = m_graphe.chercherSommetParId(idArr);
        m_graphe.supprimerArc(Arc(sDep, sArr, ancienPoids));
        m_graphe.ajouterArc(Arc(sDep, sArr, nouveauPoids));
        // ← plus de modifierPoidsVisuel ici, déjà fait dans modifierPoidsArc
    }
void InterfaceGraphique::surDemandeSuppressionSommet(int idSommet) {
    // 1. Demander confirmation
    auto rep = QMessageBox::question(this, "Supprimer sommet",
        QString("Etes-vous sûr de vouloir supprimer le sommet %1 et tous ses arcs liés ?").arg(idSommet),
        QMessageBox::Yes | QMessageBox::No);

    if (rep == QMessageBox::Yes) {
        // 2. Trouver le sommet complet à partir de l'ID
        Sommet sATrouver = m_graphe.chercherSommetParId(idSommet);

        // 3. Supprimer dans le modèle (Graphe) en utilisant la méthode existante
        m_graphe.supprimerSommet(sATrouver);

        // 3. Supprimer dans la vue (ZoneDessin)
        // Tu appelles ta fonction effacerSommet (déjà existante dans ZoneDessin)
        // Note : Il faut qu'elle soit publique pour être appelée ici
        m_zone->effacerSommetParId(idSommet);

        // 4. Mettre à jour les combobox
        synchroniserComboBoxSommets();
    }
}
InterfaceGraphique::~InterfaceGraphique()
{
    delete ui;
}