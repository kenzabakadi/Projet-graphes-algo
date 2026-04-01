#include "dijkstra.h"

Dijkstra::Dijkstra(Graphe& graphe) : Algorithme(graphe) {}

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
    vector<vector<int>> c(n+1, vector<int>(n+1, INF)); // INF lorsqu'il n'y a pas d'arête entre i et j

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
    vector<bool> marquage(n+1, true);

    distances[0] = n;
    predecesseurs[0] = n;
    marquage[sommet] = false;
    int ind = n-1;

    // Initialisation de distances et predecesseurs
    for (int i = 1; i <= n; ++i) {
        distances[i] = matriceCout[sommet][i];
        predecesseurs[i] = sommet;
    }

    while (ind > 0) {
        int min = INF;
        int j = -1;
        for (int i = 1; i <= n; ++i) {
            if (marquage[i] && distances[i] < min) {
                min = distances[i];
                j = i;
            }
        }

        if (min == INF) break;

        marquage[j] = false;
        --ind;

        for (int k = aps[j]; fs[k] != 0; ++k) {
            int t = fs[k];

            if (distances[j] != INF) {
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

    int sommetDepart = 1;
    dijkstra(sommetDepart); // exécuter depuis le sommet 1
}