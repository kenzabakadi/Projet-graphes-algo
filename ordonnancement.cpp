#include "ordonnancement.h"

Ordonnancement::Ordonnancement(Graphe& graphe) : Algorithme(graphe) {}



void Ordonnancement::calculer() {
    g.calculerFsAps(fs, aps);
    int n = aps[0];

    if (n == 0) return; 


    vector<int> d(n + 1, 0);
    for (const Arc& a : g.retournerArcs()) {
        int j = a.retournerSommetArrivee().retournerId();
        d[j] = a.retournerPoids();
    }

    int m = fs[0];
    if (m == 0) return; 


    appc.assign(m + 1, 0);
    fpc.assign(m + 1, 0);

    datesPlusTot.resize(n + 1);
    appc[0] = m;
    datesPlusTot[1] = 0;
    fpc[1] = 0;

    int kc = 1;
    for (int i = 2; i <= n; i++) {
        datesPlusTot[i] = 0;
        appc[i] = kc + 1;

        int j;
        for (int k = appc[i]; (j = fs[k]) != 0; k++) {
            int v = datesPlusTot[i] + d[j];
            if (v > datesPlusTot[i]) {
                datesPlusTot[i] = v;
                kc = appc[i];
                fpc[kc] = j;
            }
            else {
                kc++;
                fpc[kc] = j;
            }
        }

        kc++;
        fpc[kc] = 0;
    }
    fpc[0] = kc;
}

void Ordonnancement::executer() {
    calculer();
}

vector<int> Ordonnancement::retournerDatesPlusTot() const {
    return datesPlusTot;
}
