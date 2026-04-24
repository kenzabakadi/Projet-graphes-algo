#include <algorithm> // pour utiliser min()
#include "tarjan.h"

using std::min;

Tarjan::Tarjan(Graphe& graphe) : Algorithme(graphe) {}

void Tarjan::traversee(int s) {
    num[s] = ro[s] = ++compteur;
    tarj.push_back(s);
    dansTarj[s] = true;

    for (int k = aps[s]; fs[k] != 0; ++k) {
        int t = fs[k];
        if (num[t] == 0) {
            pred[t] = s;
            traversee(t);
            ro[s] = min(ro[s], num[t]);
        } else if (dansTarj[t]) {
            ro[s] = min(ro[s], num[t]);
        }
    }

    if (ro[s] == num[s]) {
        nbCFC++;
        int u; 
        do {
            u = tarj.back();
            tarj.pop_back();
            dansTarj[u] = false;

            cfc[u] = nbCFC; 
            pilch[u] = prem[nbCFC];
            prem[nbCFC] = u;
        } while (u != s);
    }
}

void Tarjan::construireGrapheReduit() {
    int nbc = nbCFC; 
    apsReduit.resize(nbc+1);
    fsReduit.clear();
    fsReduit.push_back(0);

    int kr = 1;

    for (int i = 1; i <= nbc; ++i) { // on parcours toutes les cfc 
        apsReduit[i] = kr;
        vector<bool> dejaMis(nbc+1, false); // sert à ne pas faire d'opérations inutiles si la cfc a déjà été mise dans fsReduit
        int s = prem[i];
        while (s != 0) {
            for (int k = aps[s]; fs[k] != 0; ++k) {
                int t = fs[k];  
                if (cfc[t] != i && !dejaMis[cfc[t]]) {
                    fsReduit.push_back(cfc[t]);
                    dejaMis[cfc[t]] = true;
                    kr++;
                }
            }

            s = pilch[s];
        }

        fsReduit.push_back(0);
        kr++;
    }

    fsReduit[0] = fsReduit.size() - 1;
    apsReduit[0] = nbc;
}

void Tarjan::calculerBases() {
    int nr = apsReduit[0];
    vector<int> ddir(nr+1, 0);

    for (int i = 1; i < fsReduit.size(); ++i) {
        if (fsReduit[i] != 0) {
            ddir[fsReduit[i]]++;
        }
    }

    base.clear();

    for (int i = 1; i <= nr; ++i) { // ajout des bases 
        if (ddir[i] == 0) {
            base.push_back(i);
        }
    }
}

void Tarjan::executer() {
    g.calculerFsAps(fs, aps);
    int n = aps[0];
    
    num.assign(n+1, 0);
    ro.assign(n+1, 0);
    pred.assign(n+1, 0);

    prem.assign(n+1, 0);
    pilch.assign(n+1, 0);
    cfc.assign(n+1, 0);

    dansTarj.assign(n+1, false);
    tarj.clear();

    compteur = 0; 
    nbCFC = 0;

    for (int s = 1; s <= n; ++s) {
        if (num[s] == 0) {
            traversee(s);
        }
    }

    construireGrapheReduit();
    calculerBases();
}
const vector<int>& Tarjan::retournerCfc()   const { return cfc; }
const vector<int>& Tarjan::retournerBase()  const { return base; }
const vector<int>& Tarjan::retournerPrem()  const { return prem; }
const vector<int>& Tarjan::retournerPilch() const { return pilch; }
int Tarjan::retournerNbCFC() const { return nbCFC; }