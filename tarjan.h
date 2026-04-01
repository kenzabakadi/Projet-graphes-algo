#ifndef TARJAN_H
#define TARJAN_H

#include "algorithme.h"

class Tarjan : public Algorithme {
    private: 
        int compteur; 
        int nbCFC;
        vector<int> fs;
        vector<int> aps;

        vector<int> num; // num[sommet] -> ordre de visite du DFS 
        vector<int> ro; // ro[sommet] -> plus petit num atteignable depuis s 
        vector<int> pred;

        vector<int> prem;
        vector<int> pilch;
        vector<int> cfc; 

        vector<int> tarj;
        vector<bool> dansTarj;  

        vector<int> fsReduit;
        vector<int> apsReduit;
        vector<int> base;

        void traversee(int s);
        void construireGrapheReduit();
        void calculerBases(); // il faut encore afficher les bases ! 
    public: 
        Tarjan(Graphe& graphe);
        void executer() override;
};

#endif // TARJAN_H