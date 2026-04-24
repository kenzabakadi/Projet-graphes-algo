#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits>
#include "algorithme.h"

class Dijkstra : public Algorithme {
    private: 
        vector<int> fs;
        vector<int> aps;
        vector<int> distances;
        vector<int> predecesseurs;
        vector<vector<int>> matriceCout;
        int m_sommetDepart;

        const int INFINI = std::numeric_limits<int>::max(); // limite maximale d'entier

        void verifierPoids() const;
        void recupererFsAps(vector<int>& fs, vector<int>& aps) const;
        vector<vector<int>> construireMatriceCout(int n) const;
        void dijkstra(int sommet);
    public: 
        Dijkstra(Graphe& graphe, int sommetDepart = 1); //ajouter sommet depart

        vector<int> retournerDistances() const;      // pour affichage
        vector<int> retournerPredecesseurs() const;  // pouraffichage
        void executer() override;
};

#endif // DIJKSTRA_H