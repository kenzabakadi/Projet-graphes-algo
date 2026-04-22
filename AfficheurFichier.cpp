#include "AfficheurFichier.h"
#include <iostream>
#include"graphe.h"
#include<fstream>

void AfficheurFichier::afficher(const Graphe& graphe)
{
        std::ofstream fichier(nomFichier);

        if (!fichier.is_open()) 
        {
            std::cerr << "Erreur : impossible de créer le fichier " << nomFichier << std::endl;
            return;
        }

        auto lesSommets = graphe.retournerSommets();
        auto lesArcs = graphe.retournerArcs();

//Faut ajouter estOriete  a graphe.h
        fichier << (graphe.estOriente() ? "o" : "n") << std::endl;

        // 2. Nombre de sommets
        fichier << lesSommets.size() << std::endl;

        for (const auto& s : lesSommets) {
            fichier << s.retournerDonnees() << std::endl;
        }

        fichier << lesArcs.size() << std::endl;

        for (const auto& a : lesArcs) {
            fichier << a.retournerSommetDepart().retournerId() << " "
                << a.retournerSommetArrivee().retournerId() << " "
                << a.retournerPoids() << std::endl;
        }

        fichier.close();
        std::cout << "Fichier exporte avec succes au format standard." << std::endl;
    }
