#include "AfficheurFichier.h"
#include <fstream>
#include <iostream>

// Implémentation du constructeur
// On associe la variable "nom" à notre attribut privé "nomFichier"
AfficheurFichier::AfficheurFichier(const std::string& nom) : nomFichier(nom) {
}


void AfficheurFichier::afficher(const Graphe& graphe) {
    std::ofstream fichier(nomFichier);

    if (fichier.is_open()) {
        fichier << "=== DONNEES DU GRAPHE ===" << std::endl;

        // C'est ici que l'on fera les boucles pour interroger 
        // la classe Graphe de tes camarades.faut d'abord savoir comment est la saisie 

        fichier << "Structure sauvegardee avec succes." << std::endl;

        fichier.close(); 
        std::cout << "Fichier '" << nomFichier << "' genere avec succes !" << std::endl;
    }
    else {
        std::cout << "Erreur : Impossible de creer ou d'ouvrir le fichier." << std::endl;
    }
}