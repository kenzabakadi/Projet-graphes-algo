#include "graphe.h"

Graphe::Graphe(bool oriente) : estOriente{oriente} {}

Graphe::Graphe(bool oriente, vector<int> fs, vector<int> aps) : estOriente{oriente} {
    if (aps.empty() || fs.empty() || aps[0] <= 0) {
        throw std::invalid_argument("FS/APS invalide.");
    }
    this->fs = fs;
    this->aps = aps;
    fsApsVersMatrice();
}

Graphe::Graphe(bool oriente, vector<vector<int>> matrice) : estOriente{oriente} {
    if (matrice.empty() || matrice[0].empty() || matrice[0].size() < 2) {
        throw std::invalid_argument("Matrice invalide.");
    }
    this->matrice = matrice;
    matriceVersFsAps();
}

void Graphe::ajouterSommet(Sommet s) { // Il faut mettre à jour FS/APS et la matrice 
    sommets.push_back(s);
    fsApsVersMatrice();
}

void Graphe::supprimerSommet(Sommet s) { // Il faut mettre à jour FS/APS et la matrice 
    for (auto it = sommets.begin(); it != sommets.end(); ++it) { // Utilisation d'itérateur pour utiliser .erase()
        if (*it == s) { // Il faut surcharger l'opérateur d'égalité entre les sommets 
            sommets.erase(it);
            break;
        }
    }
}

void Graphe::ajouterArc(Arc a) { // Il faut mettre à jour FS/APS et la matrice 
    arcs.push_back(a);
    fsApsVersMatrice;
}

void Graphe::supprimerArc(Arc a) { // Il faut mettre à jour FS/APS et la matrice 
    for (auto it = arcs.begin(); it != arcs.end(); ++it) {
        if (*it == a) { // Il faut surcharger l'opérateur d'égalité entre les arcs
            arcs.erase(it);
            break;
        }
    }
}

void Graphe::fsApsVersMatrice() {
    int n = aps[0];
    matrice.resize(n+1);

    for (int i = 0; i <= n; ++i) {
        matrice[i].resize(n+1);
        for (int j = 0; j <= n; ++j) {
            matrice[i][j] = 0;
        }
    }

    matrice[0][0] = n;
    matrice[0][1] = fs[0] - n;
    int k = 0;

    for (int i = 1; i <= n; ++i) {
        k = aps[i];
        while (fs[k] != 0) {
            matrice[i][fs[k]] = 1;
            ++k;
        }
    }
}

void Graphe::matriceVersFsAps() {
    int n = matrice[0][0];
    int m = matrice[0][1];

    fs.resize(n+m+1);
    fs[0] = n+m;

    aps.resize(n+1);
    aps[0] = n;

    int k = 1;
    for (int i = 1; i <= n; ++i) {
        aps[i] = k;
        for (int j = 1; j <= n; ++j) {
            if (matrice[i][j] == 1) {
                fs[k++] = j;
            }
        }
        fs[k++] = 0;
    }
}