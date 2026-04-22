#include "AfficheurConsole.h"
#include <iostream>
#include "graphe.h"

void AfficheurConsole::afficher(const Graphe& graphe)
{
    std::cout << "==RESEAU DES STATIONS==" << std::endl;

    auto lesSommets = graphe.retournerSommets();
    auto lesArcs = graphe.retournerArcs();
    std::vector<int> fs, aps;
    graphe.calculerFsAps(fs, aps);

    int n = aps[0]; // Nombre de sommets

    for (int i = 1; i <= n; i++)
    {
        std::cout << "[Station " << i << "] " << lesSommets[i - 1].retournerDonnees();

        int debut = aps[i];

        // On lit fs jusqu'à trouver le 0 sentinelle
        int j = debut;
        bool aDesTrajets = false;

        while (j < fs.size() && fs[j] != 0)
        {
            aDesTrajets = true;
            int idDestination = fs[j];

            // Trouver le poids de l'arc (Depart: i, Arrivee: idDestination)
            int poids = -1;
            for (const auto& arc : lesArcs) {
                if (arc.retournerSommetDepart().retournerId() == i &&
                    arc.retournerSommetArrivee().retournerId() == idDestination) {
                    poids = arc.retournerPoids();
                    break;
                }
            }

            std::cout << " -> Station " << idDestination << " (Poids : " << poids << ")";
            j++;
        }

        if (!aDesTrajets) {
            std::cout << " (Aucun trajet)";
        }
        std::cout << std::endl;
    }
}