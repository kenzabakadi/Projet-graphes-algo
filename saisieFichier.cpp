//
// Created by chzoe on 18/03/2026.
//

#include "saisiefichier.h"
#include "sommet.h"
#include "arc.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Format du fichier attendu :
// Ligne 1       : nombre de sommets (n)
// Lignes 2..n+1 : nom de chaque sommet (l'indice = l'identifiant, commence a 1)
// Lignes suivantes : matrice d'adjacence n x n
// pour la matrice : 0 = pas de lien, poids > 0 = arc avec ce poids
//
// Exemple pour 3 sommets :
//   3
//   Paris (ou 1)
//   Lyon (ou 2)
//   Marseille (ou 3)
//   0 10  0
//   0  0 15
//   0  0  0

SaisieFichier::SaisieFichier(const std::string& nom) : nomFichier(nom)
{}

void SaisieFichier::saisir(Graphe& graphe)
{
    std::ifstream fichier(nomFichier);

    if (!fichier.is_open())
    {
        std::cout << "Erreur : impossible d'ouvrir le fichier '" << nomFichier << "'." << std::endl;
        return;
    }

    int n;
    fichier >> n;
    fichier.ignore();

    if (n <= 0)
    {
        std::cout << "Erreur : nombre de sommets invalide." << std::endl;
        return;
    }

    for (int i = 1; i <= n; ++i)
    {
        std::string nom;
        std::getline(fichier, nom);
        Sommet s(i, nom);
        graphe.ajouterSommet(s);
    }

    for (int i = 1; i <= n; ++i)
    {
        std::string ligne;
        std::getline(fichier, ligne);
        std::istringstream iss(ligne);
        for (int j = 1; j <= n; ++j)
        {
            int poids;
            iss >> poids;
            if (poids != 0)
            {
                Sommet depart(i, "");
                Sommet arrivee(j, "");
                Arc arc(depart, arrivee, poids);
                graphe.ajouterArc(arc);
            }
        }
    }

    fichier.close();
}