// dantzig.cpp
#include "dantzig.h"

Dantzig::Dantzig(Graphe& graphe) : Algorithme(graphe) {}

void Dantzig::recupererFsAps(vector<int>& fs, vector<int>& aps) const {
    g.calculerFsAps(fs, aps);
}

vector<vector<int>> Dantzig::construireMatriceCout(int n) const {

    vector<vector<int>> c(n+2, vector<int>(n+2, INFINI));
    for (int i = 1; i <= n; ++i)
        c[i][i] = 0;
    for (const Arc& a : g.retournerArcs()) {
        int u = a.retournerSommetDepart().retournerId();
        int v = a.retournerSommetArrivee().retournerId();
        c[u][v] = a.retournerPoids();
    }
    return c;
}

bool Dantzig::dantzig() {
    int n = aps[0];
    for (int k = 2; k <= n; k++) {
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                // Protection contre l'overflow avant chaque addition
                if (matriceCout[i][j] != INFINI && matriceCout[j][k+1] != INFINI) {
                    int x = matriceCout[i][j] + matriceCout[j][k+1];
                    if (x < matriceCout[i][k+1])
                        matriceCout[i][k+1] = x;
                }
                if (matriceCout[k+1][j] != INFINI && matriceCout[j][i] != INFINI) {
                    int y = matriceCout[k+1][j] + matriceCout[j][i];
                    if (y < matriceCout[k+1][i])
                        matriceCout[k+1][i] = y;
                }
            }
            // Detection circuit absorbant
            if (matriceCout[i][k+1] != INFINI && matriceCout[k+1][i] != INFINI && matriceCout[i][k+1] + matriceCout[k+1][i] < 0)
                return false;
        }
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {
                if (matriceCout[i][k+1] != INFINI && matriceCout[k+1][j] != INFINI) {
                    int x = matriceCout[i][k+1] + matriceCout[k+1][j];
                    if (x < matriceCout[i][j])
                        matriceCout[i][j] = x;
                }
            }
        }
    }
    return true;
}

void Dantzig::executer() {
    recupererFsAps(fs, aps);
    int n = aps[0];
    matriceCout = construireMatriceCout(n);
    circuitAbsorbant = !dantzig();
}

bool Dantzig::aCircuitAbsorbant() const { return circuitAbsorbant; }

const vector<vector<int>>& Dantzig::retournerMatrice() const { return matriceCout; }
