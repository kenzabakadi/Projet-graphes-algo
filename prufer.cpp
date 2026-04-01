#include "prufer.h"

Prufer::Prufer(Graphe& graphe) : Algorithme(graphe) {}

void Prufer::executer() {
    code = coder();
}

std::vector<int> Prufer::coder() {
    int n = g.retournerSommets().size();

    std::vector<int> degres(n+1,0);
    std::vector<int> voisin(n+1,0);
    std::vector<int> resultat;
    std::vector<bool> supprime(n+1,false);

    for(const Arc& a : g.retournerArcs()) {
        int depart = a.retournerSommetDepart().retournerId();
        int arrivee = a.retournerSommetArrivee().retournerId();
        degres[depart]++;
        degres[arrivee]++;
        voisin[depart] = arrivee;
        voisin[arrivee] = depart;
    }

    for(int k = 0; k < n-2; k++) {
        for(int i = 1; i <= n; i++) {
            if(!supprime[i] && degres[i] == 1) {
                resultat.push_back(voisin[i]);
                degres[voisin[i]] --;
                supprime[i] = true;
                break;
            }
        }
    }

    return resultat;
}

void Prufer::decoder(std::vector<int> code) {
    int n = code.size()+2;
    std::vector<int> degres(n+1, 1);
    std::vector<Sommet> sommets = g.retournerSommets();

    for(int i : code) {
        degres[i]++;
    }

    for(int i : code) {
        for(int j=1; j<=n; j++) {
            if(degres[j]==1) {
                g.ajouterArc(Arc(sommets[j-1], sommets[i-1], 1));
                degres[j]--;
                degres[i]--;
                break;
            }
        }
    }

    int u =-1, v=-1;
    for(int i = 1; i<= n; i++) {
        if(degres[i] == 1) {
            if(u==-1) {
                u = i;
            } else {
                v = i;
            }
        }
    }

    g.ajouterArc(Arc(sommets[u - 1], sommets[v - 1], 1));
}

std::vector<int> Prufer::retournerCode() const {
    return code;
}