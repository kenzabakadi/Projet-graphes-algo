#include "distance.h"

Distance::Distance(Graphe& graphe, int sommetDepart)
    : Algorithme(graphe), m_sommetDepart(sommetDepart) {
}

void Distance::calculer() {
    g.calculerFsAps(fs, aps);
    int n = aps[0];

    if (n == 0) return; 

    int t = 0, q = 1, dist = 0;
    int iFin, sCourant, successeur, it;

    vector<int> file(n + 1); 

    distances.resize(n + 1);
    file[1] = m_sommetDepart;

    for (int i = 1; i <= n; i++)
        distances[i] = -1;
    distances[m_sommetDepart] = 0;

    while (t != q) {
        dist++;
        iFin = q;
        while (t < iFin) {
            t++;
            sCourant = file[t];
            it = aps[sCourant];
            successeur = fs[it];
            while (successeur != 0) {
                if (distances[successeur] == -1) {
                    q++;
                    file[q] = successeur;
                    distances[successeur] = dist;
                }
                successeur = fs[++it];
            }
        }
    }

}

void Distance::executer() {
    calculer();
}

vector<int> Distance::retournerDistances() const {
    return distances;
}
