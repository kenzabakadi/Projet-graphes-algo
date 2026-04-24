#include "graphe.h"
#include<algorithm>

Graphe::Graphe(bool oriente) : d_estOriente{oriente} {}

void Graphe::ajouterSommet(const Sommet& s) { 
    sommets.push_back(s);
}
bool Graphe::estOriente() const { return d_estOriente; }

void Graphe::supprimerSommet(const Sommet& s) { //modifier pour reendixer tous les sommets 
    int idSupprime = s.retournerId();

    // Supprimer le sommet
    for (auto it = sommets.begin(); it != sommets.end(); ++it) {
        if (*it == s) { sommets.erase(it); break; }
    }

    // Supprimer les arcs associés
    for (auto it = arcs.begin(); it != arcs.end(); ) {
        if (it->retournerSommetDepart() == s || it->retournerSommetArrivee() == s)
            it = arcs.erase(it);
        else
            ++it;
    }

    // Réindexer les sommets restants
    for (Sommet& som : sommets) {
        if (som.retournerId() > idSupprime)
            som.attribuerId(som.retournerId() - 1);
    }

    // Réindexer les arcs restants
    for (Arc& a : arcs) {
        if (a.retournerSommetDepart().retournerId() > idSupprime) {
            Sommet dep = a.retournerSommetDepart();
            dep.attribuerId(dep.retournerId() - 1);
            a.attribuerSommetDepart(dep);
        }
        if (a.retournerSommetArrivee().retournerId() > idSupprime) {
            Sommet arr = a.retournerSommetArrivee();
            arr.attribuerId(arr.retournerId() - 1);
            a.attribuerSommetArrivee(arr);
        }
    }
}

void Graphe::ajouterArc(const Arc& a) { 
    arcs.push_back(a);

    // On ajoute aussi l'arc inverse si le graphe est non-orienté (facilite les algorithmes)
    if (!estOriente()) {
        Arc inverse(
            a.retournerSommetArrivee(),
            a.retournerSommetDepart(),
            a.retournerPoids()
        );
        arcs.push_back(inverse);
    }
}

void Graphe::supprimerArc(const Arc& a) {// envlever arc inverse dans graphe non orienté
    auto nouveau_fin = std::remove_if(arcs.begin(), arcs.end(), [&](const Arc& arc_courant) {
        // Condition 1 : L'arc correspond exactement (direct)
        bool direct = (arc_courant == a);

        // Condition 2 : L'arc correspond à l'inverse (si non orienté)
        bool inverse = (!estOriente() &&
            arc_courant.retournerSommetDepart() == a.retournerSommetArrivee() &&
            arc_courant.retournerSommetArrivee() == a.retournerSommetDepart() &&
            arc_courant.retournerPoids() == a.retournerPoids());

        return direct || inverse;
        });

    // On efface réellement les éléments de la fin vers le début
    arcs.erase(nouveau_fin, arcs.end());
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
    if (estOriente() || sommets.empty()) return false;

    int n = sommets.size();
    int m = arcs.size() / 2; // car le graphe est non-orienté donc deux arcs pour chaque arête

    return estConnexe() && m == n-1;
}
// Dans graphe.cpp

Sommet Graphe::chercherSommetParId(int id) const {
    // Parcourt le vecteur des sommets pour trouver celui qui correspond à l'ID
    for (const Sommet& s : sommets) {
        if (s.retournerId() == id) {
            return s; // Sommet trouvé
        }
    }

    // Si aucun sommet n'est trouvé, on retourne un sommet par défaut 
    // ou on lève une exception selon ta gestion d'erreur.
    // Ici, on retourne un sommet avec un ID invalide (-1) :
    return Sommet(-1, "Inconnu");
}
