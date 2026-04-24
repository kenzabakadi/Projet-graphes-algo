#include "dijkstra.h"
#include"graphe.h"
#include <stdexcept> 

Dijkstra::Dijkstra(Graphe& graphe, int sommetDepart)
    : Algorithme(graphe), m_sommetDepart(sommetDepart) {
}

void Dijkstra::verifierPoids() const {
    for (const Arc& a : g.retournerArcs()) {
        if (a.retournerPoids() < 0) {
            throw std::logic_error("Dijkstra impossible : poids négatif");
        }
    }
}

void Dijkstra::recupererFsAps(vector<int>& fs, vector<int>& aps) const {
    g.calculerFsAps(fs, aps);
}

vector<vector<int>> Dijkstra::construireMatriceCout(int n) const {
    vector<vector<int>> c(n+1, vector<int>(n+1, INFINI)); // infini lorsqu'il n'y a pas d'arête entre i et j

    for (int i = 1; i <= n; ++i) {
        c[i][i] = 0;
    }

    for (const Arc& a : g.retournerArcs()) {
        int u = a.retournerSommetDepart().retournerId();
        int v = a.retournerSommetArrivee().retournerId();
        c[u][v] = a.retournerPoids();
    }

    return c;
}

void Dijkstra::dijkstra(int sommet) {
    int n = aps[0];

    distances.resize(n+1);
    predecesseurs.resize(n+1);
    vector<bool> marquage(n+1, true); // true -> sommet non encore traité

    distances[0] = n;
    predecesseurs[0] = n;

    // Initialisation de distances et predecesseurs depuis le sommet de départ 
    for (int i = 1; i <= n; ++i) {
        distances[i] = matriceCout[sommet][i];
        predecesseurs[i] = sommet;
    }

    marquage[sommet] = false; // sommet de départ traité 
    int ind = n-1; // nombre de sommets restants à traiter 

    while (ind > 0) {
        int min = INFINI;
        int j = -1;

        for (int i = 1; i <= n; ++i) { // recherche du sommet avec la plus petite distance
            if (marquage[i] && distances[i] < min) {
                min = distances[i];
                j = i;
            }
        }

        if (min == INFINI) break;

        marquage[j] = false; // sommet j validé 
        --ind;

        for (int k = aps[j]; fs[k] != 0; ++k) { // parcours des successeurs de j 
            int t = fs[k];

            if (distances[j] != INFINI) {
                int v = distances[j] + matriceCout[j][t];
                if (v < distances[t]) {
                    distances[t] = v;
                    predecesseurs[t] = j;
                }
            }
        }
    }
}

void Dijkstra::executer() {
    verifierPoids();
    recupererFsAps(fs, aps);
    int n = aps[0];
    matriceCout = construireMatriceCout(n);
    dijkstra(m_sommetDepart); // ← utilise le membre au lieu de 1
}
vector<int> Dijkstra::retournerDistances() const {
    return distances;
}

vector<int> Dijkstra::retournerPredecesseurs() const {
    return predecesseurs;
}