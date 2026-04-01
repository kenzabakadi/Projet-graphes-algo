#include "graphe.h"

Graphe::Graphe(bool oriente) : estOriente{oriente} {}

void Graphe::ajouterSommet(const Sommet& s) { 
    sommets.push_back(s);
}

void Graphe::supprimerSommet(const Sommet& s) {
    for (auto it = sommets.begin(); it != sommets.end(); ++it) { // Utilisation d'itérateur pour utiliser .erase()
        if (*it == s) { // Surcharge de l'opérateur d'égalité entre les sommets 
            sommets.erase(it);
            break;
        }
    }

    // Supprimer aussi les arcs associés au sommet 
    for (auto it = arcs.begin(); it != arcs.end(); ) { // Pas de troisième paramètre car erase() incrémente tout seul
        if (it->retournerSommetDepart() == s || it->retournerSommetArrivee() == s) {
            it = arcs.erase(it); // erase(it) renvoie déjà le prochain itérateur
        } else {
            ++it;
        }
    }
}

void Graphe::ajouterArc(const Arc& a) { 
    arcs.push_back(a);

    // On ajoute aussi l'arc inverse si le graphe est non-orienté (facilite les algorithmes)
    if (!estOriente) {
        Arc inverse(
            a.retournerSommetArrivee(),
            a.retournerSommetDepart(),
            a.retournerPoids()
        );
        arcs.push_back(inverse);
    }
}

void Graphe::supprimerArc(const Arc& a) { 
    for (auto it = arcs.begin(); it != arcs.end(); ++it) {
        if (*it == a) { // Surcharge de l'opérateur d'égalité entre les arcs
            arcs.erase(it);
            break;
        }
    }
}

vector<Sommet> Graphe::retournerSommets() const {
    return sommets;
}

vector<Arc> Graphe::retournerArcs() const {
    return arcs;
}

vector<vector<int>> Graphe::retournerMatrice() const {
    int n = sommets.size();
    int m = arcs.size();
    vector<vector<int>> matrice(n+1, vector<int>(n+1, 0));
    matrice[0][0] = n;
    matrice[0][1] = n+m;

    for (const Arc& a : arcs) {
        int i = a.retournerSommetDepart().retournerId();
        int j = a.retournerSommetArrivee().retournerId();
        matrice[i][j] = 1;
    }

    return matrice;
}

void Graphe::calculerFsAps(vector<int>& fs, vector<int>& aps) const {
    int n = sommets.size();
    vector<vector<int>> successeurs(n + 1);

    for (const Arc& a : arcs) {
        int u = a.retournerSommetDepart().retournerId();
        int v = a.retournerSommetArrivee().retournerId();
        successeurs[u].push_back(v);
    }

    fs.clear();
    aps.resize(n + 1);
    fs.push_back(0); 
    int k = 1;

    for (int i = 1; i <= n; ++i) {
        aps[i] = k;

        for (int v : successeurs[i]) {
            fs.push_back(v);
            k++;
        }

        fs.push_back(0);
        k++;
    }

    fs[0] = fs.size() - 1;
    aps[0] = n;
}



bool Graphe::estConnexe() const {
    int n = sommets.size();
    vector<bool> visite(n+1, false); // car les id des sommets commencent à 1 (pas de sommet 0)
    int depart = sommets[0].retournerId();
    dfs(depart, visite);

    for (const Sommet& s : sommets) {
        if (!visite[s.retournerId()]) {
            return false;
        }
    }

    return true;
}

void Graphe::dfs(int sommet, vector<bool>& visite) const {
    visite[sommet] = true;

    for (const Arc& a : arcs) {
        if (a.retournerSommetDepart().retournerId() == sommet) {
            int voisin = a.retournerSommetArrivee().retournerId();
            if (!visite[voisin]) {
                dfs(voisin, visite);
            }
        }
    }
}

bool Graphe::estUnArbre() const {
    if (estOriente || sommets.empty()) return false;

    int n = sommets.size();
    int m = arcs.size() / 2; // car le graphe est non-orienté donc deux arcs pour chaque arête

    return estConnexe() && m == n-1;
}