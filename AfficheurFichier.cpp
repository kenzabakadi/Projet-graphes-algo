#include "AfficheurFichier.h"
#include <iostream>
#include <fstream>
#include "graphe.h"

void AfficheurFichier::afficher(const Graphe& graphe) {
    // Ici, nomFichier est directement accessible car il appartient à la classe
    std::ofstream fichier(nomFichier);

    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible de creer le fichier " << nomFichier << std::endl;
        return;
    }

    auto lesSommets = graphe.retournerSommets();
    auto lesArcs = graphe.retournerArcs();

    // 1. Orientation
    fichier << (graphe.estOriente() ? "o" : "n") << std::endl;

    // 2. Nombre de sommets
    fichier << lesSommets.size() << std::endl;

    // 3. Noms des sommets
    for (const auto& s : lesSommets) {
        fichier << s.retournerDonnees() << std::endl;
    }

    // 4. Nombre d'arcs
    fichier << lesArcs.size() << std::endl;

    // 5. Liste des arcs
    for (const auto& a : lesArcs) {
        fichier << a.retournerSommetDepart().retournerId() << " "
            << a.retournerSommetArrivee().retournerId() << " "
            << a.retournerPoids() << std::endl;
    }

    fichier.close();
}