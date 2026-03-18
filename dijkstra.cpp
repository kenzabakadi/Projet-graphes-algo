#include "dijkstra.h"

Dijkstra::Dijkstra(Graphe* graphe) : Algorithme(graphe) {}

void Dijkstra::verifierPoids() const {
    for (const Arc& a : g->retournerArcs()) {
        if (a.retournerPoids() < 0) {
            throw std::logic_error("Dijkstra impossible : poids négatif");
        }
    }
}

void Dijkstra::recupererFsAps(vector<int>& fs, vector<int>& aps) const {
    g->calculerFsAps(fs, aps);
}

vector<vector<int>> Dijkstra::construireMatriceCout(int n) const {
    const int MAXPOIDS = 100;
    vector<vector<int>> c(n+1, vector<int>(n+1, MAXPOIDS));

    for (int i = 1; i <= n; ++i) {
        c[i][i] = 0;
    }

    for (const Arc& a : g->retournerArcs()) {
        int u = a.retournerSommetDepart().retournerId();
        int v = a.retournerSommetArrivee().retournerId();
        c[u][v] = a.retournerPoids();
    }

    return c;
}

void Dijkstra::executer() {
    verifierPoids();
    matriceCout = construireMatriceCout();
    dijkstra();
}