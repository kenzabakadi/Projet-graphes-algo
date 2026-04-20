#include "AfficheurConsole.h"
#include <iostream>

void AfficheurConsole::afficher(const Graphe& graphe)
{
    std::cout << "== RESEAU DES STATIONS ==" << std::endl;

    // On récupère directement les listes
    auto lesSommets = graphe.retournerSommets();
    auto lesArcs = graphe.retournerArcs();

    // On parcourt chaque station
    for (const auto& sommet : lesSommets)
    {
        // Affichage de la station (le nom est dans "donnees")
        std::cout << "\n[Station " << sommet.retournerId() << "] "
            << sommet.retournerDonnees() << std::endl;

        bool aDesTrajets = false;

        // On cherche les arcs qui partent de cette station
        for (const auto& arc : lesArcs)
        {
            if (arc.retournerSommetDepart() == sommet)
            {
                std::cout << "  -> reliee a : Station "
                    << arc.retournerSommetArrivee().retournerId()
                    << " (Poids : " << arc.retournerPoids() << ")" << std::endl;

                aDesTrajets = true; // On a trouvé un trajet
            }
        }
        if (!aDesTrajets)
        {
            std::cout << "  (Aucun trajet au depart de cette station)" << std::endl;
        }
    }
}