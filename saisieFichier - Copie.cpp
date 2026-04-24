#include "saisiefichier.h"
#include "sommet.h"
#include "arc.h"
#include <fstream>
#include <iostream>
#include <sstream>

/*
// Exemple de fichier :
o
3
Paris
Lyon
Marseille
3
1 2 -5
2 3 4
1 3 0
*/

SaisieFichier::SaisieFichier(const std::string& nom) : nomFichier(nom) {}

bool SaisieFichier::ouvrirFichier(std::ifstream& fichier) const {
    fichier.open(nomFichier);
    if (!fichier.is_open()) {
        std::cout << "Erreur : impossible d'ouvrir le fichier '" << nomFichier << "'." << std::endl;
        return false;
    }
    return true;
}

void SaisieFichier::lireSommets(std::ifstream& fichier, Graphe& graphe, std::vector<Sommet>& listeSommets, int n) const {
    for (int i = 1; i <= n; ++i) {
        std::string nom;
        std::getline(fichier, nom);
        Sommet s(i, nom);
        listeSommets.push_back(s);
        graphe.ajouterSommet(s);
    }
}

void SaisieFichier::lireArcs(std::ifstream& fichier, Graphe& graphe, std::vector<Sommet>& listeSommets, int n, int m, bool oriente) const {
    int lus = 0;
    std::string ligne;

    while (lus < m && std::getline(fichier, ligne)) {
        if (!ligne.empty()) {
            std::istringstream iss(ligne);
            int idDepart, idArrivee, poids;

            if (iss >> idDepart >> idArrivee >> poids) {
                if (idDepart < 1 || idDepart > n || idArrivee < 1 || idArrivee > n) {
                    std::cout << "Erreur : arc invalide (" << idDepart << " -> " << idArrivee << ")." << std::endl;
                } else {
                    Arc arc(listeSommets[idDepart - 1], listeSommets[idArrivee - 1], poids);
                    graphe.ajouterArc(arc);
                }
                lus++;
            }
        }
    }
}

void SaisieFichier::saisir(Graphe& graphe) {
    std::ifstream fichier;
    if (!ouvrirFichier(fichier)) return;

    std::string orientation;
    std::getline(fichier, orientation);
    bool oriente = (orientation == "o");
    graphe = Graphe(oriente);// cree un nouveau graphe avec orientation 

    int n;
    fichier >> n;
    fichier.ignore();
    if (n <= 0) {
        std::cout << "Erreur : nombre de sommets invalide." << std::endl;
        return;
    }

    std::vector<Sommet> listeSommets;
    lireSommets(fichier, graphe, listeSommets, n);

    int m;
    fichier >> m;
    fichier.ignore();
    if (m < 0) {
        std::cout << "Erreur : nombre d'arcs invalide." << std::endl;
        return;
    }

    lireArcs(fichier, graphe, listeSommets, n, m, oriente);

    fichier.close();
    std::cout << "Graphe charge depuis '" << nomFichier << "' avec succes !" << std::endl;
}