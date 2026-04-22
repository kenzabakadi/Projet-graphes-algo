#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>
#include "sommet.h"
#include "arc.h"

using std::vector;

class Graphe {
    private: 
        bool d_estOriente;
        // vector<vector<int>> matrice; nouvelle logique : on passe tout par sommets et arcs et on utilise fs et aps seulement dans les algos
        // vector<int> fs;
        // vector<int> aps;
        vector<Sommet> sommets;
        vector<Arc> arcs; // rajout d'un tableau d'arcs oublié dans le diagramme UML 
    public:
        // Constructeur 
        Graphe(bool oriente = false);
        bool estOriente()const ;

        // Gestion des sommets 
        void ajouterSommet(const Sommet& s);
        Sommet chercherSommetParId(int id) const;
        void supprimerSommet(const Sommet& s);

        // Gestion des arcs 
        void ajouterArc(const Arc& a);
        void supprimerArc(const Arc& a);

        // Accès 
        vector<Sommet> retournerSommets() const;
        vector<Arc> retournerArcs() const;

        // Représentations calculées 
        vector<vector<int>> retournerMatrice() const;
        void calculerFsAps(vector<int>& fs, vector<int>& aps) const;

        // Permet de tester si le graphe est un arbre
        void dfs(int sommet, vector<bool>& visite) const;
        bool estConnexe() const;
        bool estUnArbre() const;

        // Sauvergarder et charger un graphe n'est pas de la responsabilité du graphe, il faut changer ça
};

#endif // GRAPHE_H