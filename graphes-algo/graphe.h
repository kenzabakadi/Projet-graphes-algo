#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>
#include "sommet.h"
#include "arc.h"

using std::vector;

class Graphe {
    private: 
        bool estOriente;
        vector<vector<int>> matrice;
        vector<int> fs;
        vector<int> aps;
        vector<Sommet> sommets;
        vector<Arc> arcs; // rajout d'un tableau d'arcs oublié dans le diagramme UML 
    public:
        Graphe(bool oriente);
        Graphe(bool oriente, vector<int> fs, vector<int> aps);
        Graphe(bool oriente, vector<vector<int>> matrice);
        void ajouterSommet(Sommet s);
        void supprimerSommet(Sommet s);
        void ajouterArc(Arc a);
        void supprimerArc(Arc a);
        void fsApsVersMatrice();
        void matriceVersFsAps();
        // Sauvergarder et charger un graphe n'est pas de la responsabilité du graphe, il faut changer ça
};

#endif // GRAPHE_H