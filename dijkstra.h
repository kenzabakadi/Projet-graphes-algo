#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "algorithme.h"

class Dijkstra : public Algorithme {
    private: 
        vector<int> fs;
        vector<int> aps;
        vector<int> distances;
        vector<int> predecesseur;
        vector<vector<int>> matriceCout;

        void verifierPoids() const;
        void recupererFsAps(vector<int>& fs, vector<int>& aps) const;
        vector<vector<int>> construireMatriceCout(int n) const;
        void dijkstra(int s, const vector<int>& fs, const vector<int>& aps, const vector<vector<int>> c, vector<int>& d);
    public: 
        Dijkstra(Graphe* graphe);
        void executer() override;
};

#endif // DIJKSTRA_H