#include "InterfaceGraphique.h"
#include "ui_interface.h"
#include "graphe.h"
#include "zonedessin.h"
#include"dijkstra.h"
#include"ResultatAlgo.h"
#include"dantzig.h"
#include "distance.h"
#include "kruskal.h"
#include "ordonnancement.h"
#include "prufer.h"
#include "rang.h"
#include "tarjan.h"
#include"AfficheurFichier.h"
#include"saisieFichier.h"
#include <map>
#include <QFileDialog>
#include "saisieclavier.h"
#include"FenetreResultat.h"

InterfaceGraphique::InterfaceGraphique(Graphe& graphe, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::FenetreGraphe), m_graphe(graphe)
{
    ui->setupUi(this);

    // 1. Mise en place de la zone de dessin manuelle
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->ongletGraphique->layout());
    layout->removeWidget(ui->zoneDessinGraphe);
    delete ui->zoneDessinGraphe;

    m_zone = new ZoneDessin(m_graphe.estOriente(), this);
    layout->addWidget(m_zone);

    // 2. Initialisation des données de test
    ui->btnSupprimerArc->setEnabled(false);
    ui->btnModifierArc->setEnabled(false);
    if (m_zone)
        m_zone->chargerDepuisGraphe(m_graphe);

    // 3. Mise à jour initiale des ComboBox
    synchroniserComboBoxSommets();
    // Dans le constructeur, juste avant l'accolade fermante "}"
    mettreAJourDonneesBrutes();
    //Synchroniser ajout des sommet avec list 
    connect(m_zone, &ZoneDessin::sommetAjouteSignal, this, &InterfaceGraphique::surNouveauSommetAjoute);
    // Ajoute cette ligne dans le constructeur, juste après ui->setupUi(this);
    //connect(ui->btnAjouterArc, &QPushButton::clicked, this, &InterfaceGraphique::on_btnAjouterArc_clicked);
    connect(m_zone, &ZoneDessin::arcCliqueSignal, this, &InterfaceGraphique::surArcSelectionne);
    connect(m_zone, &ZoneDessin::arcDeselectionneSignal, this, &InterfaceGraphique::surArcDeselectionne);
    connect(m_zone, &ZoneDessin::arcModifieSignal, this, &InterfaceGraphique::surArcModifie);
    connect(m_zone, &ZoneDessin::demanderSuppressionSommetSignal, this, &InterfaceGraphique::surDemandeSuppressionSommet);
    //connect(ui->btnLancerAlgorithme, &QPushButton::clicked, this, &InterfaceGraphique::on_btnLancerAlgorithme_clicked);
    //connect(ui->btnChargerFichier, &QPushButton::clicked, this, &InterfaceGraphique::on_btnChargerFichier_clicked);
    connect(ui->btnSauvgarderFichier, &QPushButton::clicked, this, &InterfaceGraphique::on_btnSauvegarderFichier_clicked);
    //connect(ui->btnSaisieClavier, &QPushButton::clicked, this, &InterfaceGraphique::on_btnSaisieClavier_clicked);
}


void InterfaceGraphique::on_btnAjouterArc_clicked() {
    int idDep = ui->comboSommetSource->currentData().toInt();
    int idArr = ui->comboSommetDestination->currentData().toInt();

    if (ui->inputPoidsArc->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un poids valide.");
        return;
    }
    int poids = ui->inputPoidsArc->text().trimmed().toInt();

    // Vérifier doublon — en non orienté, vérifier les deux sens
    for (const Arc& a : m_graphe.retournerArcs()) {
        int dep = a.retournerSommetDepart().retournerId();
        int arr = a.retournerSommetArrivee().retournerId();

        bool doublonDirect = (dep == idDep && arr == idArr);
        bool doublonInverse = !m_graphe.estOriente() && (dep == idArr && arr == idDep);

        if (doublonDirect || doublonInverse) {
            QMessageBox::warning(this, "Erreur", "Cet arc existe déjà.");
            return;
        }
    }

    Sommet sDep = m_graphe.chercherSommetParId(idDep);
    Sommet sArr = m_graphe.chercherSommetParId(idArr);
    m_graphe.ajouterArc(Arc(sDep, sArr, poids));
    m_zone->ajouterArcDeLExterieur(idDep, idArr, poids);
    ui->inputPoidsArc->clear();
    mettreAJourDonneesBrutes();
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
    mettreAJourDonneesBrutes();
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
    mettreAJourDonneesBrutes();
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
        m_zone->chargerDepuisGraphe(m_graphe);

        // 4. Mettre à jour les combobox
        synchroniserComboBoxSommets();
        mettreAJourDonneesBrutes();
    }
}
void InterfaceGraphique::on_btnLancerAlgorithme_clicked() {
    qDebug() << "Bouton lancé !";
    QString algo = ui->comboAlgorithme->currentText();
    qDebug() << "Algo sélectionné :" << algo;
    if (algo == "Dijkstra")
        lancerDijkstra();
    else if (algo == "Dantzig")
        lancerDantzig();
    else if (algo == "Distance")
        lancerDistance();
    else if (algo == "Kruskal")
        lancerKruskal();
    else if (algo == "Ordonancement")
        lancerOrdonnancement();
    else if (algo == "Prufer")
        lancerPrufer();
    else if (algo == "Rang")
        lancerRang();
    else if (algo == "Tarjan")
        lancerTarjan();
}

void InterfaceGraphique::lancerDijkstra() {
    bool ok;
    int sommetDepart = QInputDialog::getInt(this, "Dijkstra",
        "Sommet de départ :", 1, 1,
        m_graphe.retournerSommets().size(), 1, &ok);
    if (!ok) return;

    try {
        Dijkstra d(m_graphe, sommetDepart);
        d.executer();

        vector<int> distances = d.retournerDistances();
        vector<int> predecesseurs = d.retournerPredecesseurs();

        QString resultat = "<h3>Dijkstra depuis : <b>" +
            QString::fromStdString(m_graphe.chercherSommetParId(sommetDepart).retournerDonnees()) +
            "</b></h3>";
        resultat += "<table border='1' cellpadding='5'>";
        resultat += "<tr><th>Sommet</th><th>Distance</th><th>Chemin</th></tr>";

        std::vector<int> tousLesSommets;
        std::vector<std::pair<int, int>> tousLesArcs;

        for (const Sommet& s : m_graphe.retournerSommets()) {
            int id = s.retournerId();
            QString nom = QString::fromStdString(s.retournerDonnees());
            int dist = distances[id];

            // Reconstituer le chemin
            QString chemin = nom;
            int pred = id;
            int securite = 0;

            std::vector<int> cheminIds = { id };
            int predCourant = id;
            while (predecesseurs[predCourant] != predCourant && securite < 100) {
                int suivant = predecesseurs[predCourant];
                tousLesArcs.push_back({ suivant, predCourant });
                predCourant = suivant;
                cheminIds.push_back(predCourant);
                chemin = QString::fromStdString(
                    m_graphe.chercherSommetParId(predCourant).retournerDonnees()) + " → " + chemin;
                securite++;
            }
            for (int sid : cheminIds) tousLesSommets.push_back(sid);

            QString distStr = (dist == std::numeric_limits<int>::max()) ?
                "Inaccessible" : QString::number(dist);

            resultat += "<tr><td>" + nom + "</td><td>" + distStr +
                "</td><td>" + chemin + "</td></tr>";
        }
        resultat += "</table>";

        // Supprimer les doublons
        std::sort(tousLesSommets.begin(), tousLesSommets.end());
        tousLesSommets.erase(std::unique(tousLesSommets.begin(), tousLesSommets.end()), tousLesSommets.end());

        FenetreResultat fenetre("Résultats Dijkstra", resultat, m_graphe, this,
            tousLesSommets, tousLesArcs);
        fenetre.exec();

    }
    catch (std::logic_error& e) {
        QMessageBox::warning(this, "Erreur Dijkstra", QString::fromStdString(e.what()));
    }
}
void InterfaceGraphique::lancerDantzig() {
    try {
        Dantzig d(m_graphe);
        d.executer();

        if (d.aCircuitAbsorbant()) {
            QMessageBox::warning(this, "Dantzig", "Le graphe contient un circuit absorbant.");
            return;
        }

        const vector<vector<int>>& matrice = d.retournerMatrice();
        vector<Sommet> sommets = m_graphe.retournerSommets();

        QString resultat = "<h3>Matrice des plus courts chemins (Dantzig)</h3>";
        resultat += "<table border='1' cellpadding='5'><tr><th></th>";
        for (const Sommet& s : sommets)
            resultat += "<th>" + QString::fromStdString(s.retournerDonnees()) + "</th>";
        resultat += "</tr>";
        for (const Sommet& si : sommets) {
            resultat += "<tr><td><b>" + QString::fromStdString(si.retournerDonnees()) + "</b></td>";
            for (const Sommet& sj : sommets) {
                int val = matrice[si.retournerId()][sj.retournerId()];
                QString cellule = (val >= std::numeric_limits<int>::max() / 2) ? "∞" : QString::number(val);
                resultat += "<td>" + cellule + "</td>";
            }
            resultat += "</tr>";
        }
        resultat += "</table>";

        FenetreResultat fenetre("Résultats Dantzig", resultat, m_graphe, this);
        fenetre.exec();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Erreur Dantzig", QString::fromStdString(e.what()));
    }
}
void InterfaceGraphique::lancerDistance() {
    bool ok;
    int sommetDepart = QInputDialog::getInt(this, "Distance",
        "Sommet de départ :", 1, 1, m_graphe.retournerSommets().size(), 1, &ok);
    if (!ok) return;

    Distance d(m_graphe, sommetDepart);
    d.executer();
    vector<int> distances = d.retournerDistances();

    QString resultat = "<h3>Distances depuis : <b>" +
        QString::fromStdString(m_graphe.chercherSommetParId(sommetDepart).retournerDonnees()) +
        "</b></h3>";
    resultat += "<table border='1' cellpadding='5'><tr><th>Sommet</th><th>Distance</th></tr>";

    std::vector<int> sommetsAccessibles = { sommetDepart };
    for (const Sommet& s : m_graphe.retournerSommets()) {
        int id = s.retournerId();
        int dist = distances[id];
        QString distStr = (dist == -1) ? "Inaccessible" : QString::number(dist);
        resultat += "<tr><td>" + QString::fromStdString(s.retournerDonnees()) +
            "</td><td>" + distStr + "</td></tr>";
        if (dist != -1) sommetsAccessibles.push_back(id);
    }
    resultat += "</table>";

    FenetreResultat fenetre("Résultats Distance", resultat, m_graphe, this, sommetsAccessibles);
    fenetre.exec();
}
void InterfaceGraphique::lancerKruskal() {
    try {
        Kruskal k(m_graphe);
        k.executer();

        const std::vector<Kruskal::Arete>& arbre = k.retournerArbre();
        int poidsTotal = k.retournerPoidsTotal();

        QString resultat = "<h3>Arbre couvrant minimal (Kruskal)</h3>";
        resultat += "<p><b>Poids total : " + QString::number(poidsTotal) + "</b></p>";
        resultat += "<table border='1' cellpadding='5'><tr><th>Départ</th><th>Arrivée</th><th>Poids</th></tr>";

        std::vector<int> sommetsArbre;
        std::vector<std::pair<int, int>> arcsArbre;

        for (const Kruskal::Arete& a : arbre) {
            QString nomDep = QString::fromStdString(m_graphe.chercherSommetParId(a.s).retournerDonnees());
            QString nomArr = QString::fromStdString(m_graphe.chercherSommetParId(a.t).retournerDonnees());
            resultat += "<tr><td>" + nomDep + "</td><td>" + nomArr +
                "</td><td>" + QString::number(a.poids) + "</td></tr>";
            sommetsArbre.push_back(a.s);
            sommetsArbre.push_back(a.t);
            arcsArbre.push_back({ a.s, a.t });
        }
        resultat += "</table>";

        FenetreResultat fenetre("Résultats Kruskal", resultat, m_graphe, this, sommetsArbre, arcsArbre);
        fenetre.exec();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Erreur Kruskal", QString::fromStdString(e.what()));
    }
}
void InterfaceGraphique::lancerOrdonnancement() {
    try {
        // 1. Synchronisation
        m_graphe = Graphe(m_graphe.estOriente());
        if (!m_zone->confirmer(m_graphe)) {
            QMessageBox::warning(this, "Erreur", "Le graphe est vide !");
            return;
        }
        std::map<int, int> durees;
        for (const Sommet& s : m_graphe.retournerSommets()) {
            bool ok;
            int d = QInputDialog::getInt(this, "Durée",
                "Durée de la tâche " + QString::fromStdString(s.retournerDonnees()) + " :",
                0, 0, 999, 1, &ok);
            durees[s.retournerId()] = ok ? d : 0;
        }
        Ordonnancement o(m_graphe);
        o.setDurees(durees);
        o.executer();
        vector<int> dates = o.retournerDatesPlusTot();
        QString resultat = "<h3>Ordonnancement — Dates au plus tôt</h3>";
        resultat += "<table border='1' cellpadding='5'>";
        resultat += "<tr><th>Tâche</th><th>Durée</th><th>Date au plus tôt</th></tr>";

        std::vector<int> tousLesSommets;
        for (const Sommet& s : m_graphe.retournerSommets()) {
            int id = s.retournerId();
            QString nom = QString::fromStdString(s.retournerDonnees());

            // On va chercher la durée dans la map que tu as saisie
            QString dureeStr = QString::number(durees[id]);
            QString dateStr = (id < (int)dates.size()) ? QString::number(dates[id]) : "0";

            resultat += "<tr><td>" + nom + "</td><td>" + dureeStr + "</td><td>" + dateStr + "</td></tr>";
            tousLesSommets.push_back(id);
        }
        resultat += "</table>";

        FenetreResultat fenetre("Résultats Ordonnancement", resultat, m_graphe, this, tousLesSommets);
        fenetre.exec();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Erreur", QString::fromStdString(e.what()));
    }
}
void InterfaceGraphique::lancerPrufer() {
    if (!m_graphe.estUnArbre()) {
        QMessageBox::warning(this, "Erreur Prüfer", "Prüfer nécessite un arbre non orienté !");
        return;
    }
    try {
        Prufer p(m_graphe);
        p.executer();
        std::vector<int> code = p.retournerCode();

        QString resultat = "<h3>Code de Prüfer</h3>";
        if (code.empty()) {
            resultat += "<p>Code vide (arbre à 2 sommets).</p>";
        }
        else {
            resultat += "<p>Code : <b>";
            for (int i = 0; i < (int)code.size(); i++) {
                if (i > 0) resultat += ", ";
                resultat += QString::number(code[i]);
            }
            resultat += "</b></p>";
        }

        FenetreResultat fenetre("Résultats Prüfer", resultat, m_graphe, this);
        fenetre.exec();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Erreur Prüfer", QString::fromStdString(e.what()));
    }
}
void InterfaceGraphique::lancerRang() {
    try {
        Rang r(m_graphe);
        r.executer();

        if (r.contientCircuit()) {
            QMessageBox::warning(this, "Rang", "Circuit détecté — rangs impossibles.");
            return;
        }

        vector<int> rangs = r.retournerRangs();
        QString resultat = "<h3>Rangs des sommets</h3>";
        resultat += "<table border='1' cellpadding='5'><tr><th>Sommet</th><th>Rang</th></tr>";

        std::vector<int> tousLesSommets;
        for (const Sommet& s : m_graphe.retournerSommets()) {
            int id = s.retournerId();
            QString rang = (id < (int)rangs.size()) ? QString::number(rangs[id]) : "?";
            resultat += "<tr><td>" + QString::fromStdString(s.retournerDonnees()) +
                "</td><td>" + rang + "</td></tr>";
            tousLesSommets.push_back(id);
        }
        resultat += "</table>";

        FenetreResultat fenetre("Résultats Rang", resultat, m_graphe, this, tousLesSommets);
        fenetre.exec();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Erreur Rang", QString::fromStdString(e.what()));
    }
}
void InterfaceGraphique::lancerTarjan() {
    try {
        Tarjan t(m_graphe);
        t.executer();

        int nbCFC = t.retournerNbCFC();
        const vector<int>& prem = t.retournerPrem();
        const vector<int>& pilch = t.retournerPilch();
        const vector<int>& base = t.retournerBase();

        QString resultat = "<h3>Composantes Fortement Connexes (Tarjan)</h3>";
        resultat += "<p><b>Nombre de CFC : " + QString::number(nbCFC) + "</b></p>";
        resultat += "<table border='1' cellpadding='5'><tr><th>CFC</th><th>Sommets</th><th>Base ?</th></tr>";

        std::vector<int> tousLesSommets;
        for (int i = 1; i <= nbCFC; i++) {
            QString sommets = "";
            int s = prem[i];
            while (s != 0) {
                if (!sommets.isEmpty()) sommets += ", ";
                sommets += QString::fromStdString(m_graphe.chercherSommetParId(s).retournerDonnees());
                tousLesSommets.push_back(s);
                s = pilch[s];
            }
            bool estBase = std::find(base.begin(), base.end(), i) != base.end();
            resultat += "<tr><td>CFC " + QString::number(i) + "</td><td>" +
                sommets + "</td><td>" + (estBase ? "✓ Base" : "") + "</td></tr>";
        }
        resultat += "</table>";

        FenetreResultat fenetre("Résultats Tarjan", resultat, m_graphe, this, tousLesSommets);
        fenetre.exec();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Erreur Tarjan", QString::fromStdString(e.what()));
    }
}
void InterfaceGraphique::on_btnChargerFichier_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir un graphe", "", "Fichiers texte (*.txt)");
    if (fileName.isEmpty()) return;

    // Utilisation de ta classe SaisieFichier
    SaisieFichier loader(fileName.toStdString());

    // On réinitialise le modèle avant de charger
    m_graphe = Graphe(false); // Réinitialise ton graphe
    loader.saisir(m_graphe);

    // On met à jour la vue (ZoneDessin)
    if (m_zone) {
        m_zone->setOriente(m_graphe.estOriente());
        m_zone->chargerDepuisGraphe(m_graphe);
    }
    synchroniserComboBoxSommets();
    mettreAJourDonneesBrutes();
    QMessageBox::information(this, "Succès", "Graphe chargé avec succès.");
}
void InterfaceGraphique::on_btnSauvegarderFichier_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder le graphe", "", "Fichiers texte (*.txt)");

    if (fileName.isEmpty()) return;

    // ICI : On passe le nom au constructeur
    AfficheurFichier saver(fileName.toStdString());

    saver.afficher(m_graphe);

    QMessageBox::information(this, "Succès", "Graphe sauvegardé dans : " + fileName);
}
void InterfaceGraphique::on_btnSaisieClavier_clicked() {
    // 1. On crée l'objet saisie (en lui passant 'this' comme parent pour la fenêtre)
    SaisieClavier saisie(this);

    // 2. On lance la saisie. Cela va ouvrir le dialogue et modifier m_graphe directement
    saisie.saisir(m_graphe);

    // 3. IMPORTANT : Après la saisie, il faut rafraîchir l'interface
    // Pour que la zone de dessin affiche les nouveaux sommets/arcs
    m_zone->setOriente(m_graphe.estOriente());
    m_zone->chargerDepuisGraphe(m_graphe);
    synchroniserComboBoxSommets();
    mettreAJourDonneesBrutes();
}
void InterfaceGraphique::mettreAJourDonneesBrutes() {
    // 1. Mise à jour des Sommets
    ui->textSommets->clear(); // Vide la liste
    for (const auto& s : m_graphe.retournerSommets()) {
        QString ligne = QString("ID %1 : %2").arg(s.retournerId()).arg(QString::fromStdString(s.retournerDonnees()));
        ui->textSommets->addItem(ligne); // Ajoute un élément
    }

    // 2. Mise à jour des Arcs
    ui->textArcs->clear();
    for (const auto& a : m_graphe.retournerArcs()) {
        QString ligne = QString("%1 -> %2 (Poids: %3)")
            .arg(a.retournerSommetDepart().retournerId())
            .arg(a.retournerSommetArrivee().retournerId())
            .arg(a.retournerPoids());
        ui->textArcs->addItem(ligne);
    }
}
InterfaceGraphique::~InterfaceGraphique()
{
    delete ui;
}