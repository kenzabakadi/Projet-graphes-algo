#include "ordonnancement.h"
#include <QInputDialog>
#include <map>

Ordonnancement::Ordonnancement(Graphe& graphe) : Algorithme(graphe) {}

void Ordonnancement::calculer() {
    int n = static_cast<int>(g.retournerSommets().size());
    if (n == 0) return;

    datesPlusTot.assign(n + 1, 0);

    // Calcul des degrés entrants
    vector<int> ddi(n + 1, 0);
    for (const Arc& a : g.retournerArcs()) {
        ddi[a.retournerSommetArrivee().retournerId()]++;
    }

    vector<int> file;
    for (int i = 1; i <= n; i++) {
        if (ddi[i] == 0) file.push_back(i);
    }

    size_t index = 0;
    while (index < file.size()) {
        int u = file[index++];

        // Utilise la map m_durees reçue de l'interface
        int finU = datesPlusTot[u] + m_durees[u];

        for (const Arc& a : g.retournerArcs()) {
            if (a.retournerSommetDepart().retournerId() == u) {
                int v = a.retournerSommetArrivee().retournerId();
                if (finU > datesPlusTot[v]) {
                    datesPlusTot[v] = finU;
                }
                ddi[v]--;
                if (ddi[v] == 0) file.push_back(v);
            }
        }
    }
}

void Ordonnancement::executer() {
    calculer();
}

vector<int> Ordonnancement::retournerDatesPlusTot() const {
    return datesPlusTot;
}