#include "prufer.h"
#include <QDebug>

Prufer::Prufer(Graphe& graphe) : Algorithme(graphe) {}

void Prufer::executer() {
    code = coder();
}

std::vector<int> Prufer::coder() {//mofidier pour tenier compte des double arc dans graphe non orienté 
    int n = g.retournerSommets().size();
    if (n < 2) return {};

    // Calcul des degrés
    std::vector<int> degres(n + 1, 0);
    for (const Arc& a : g.retournerArcs()) {
        int u = a.retournerSommetDepart().retournerId();
        int v = a.retournerSommetArrivee().retournerId();

        // Si le graphe est non orienté, on ne compte l'arc qu'une fois
        // (par exemple, seulement si u < v)
        if (!g.estOriente() && u > v) continue;

        degres[u]++;
        degres[v]++;
    }

    // DEBUG : Vérifier si on a bien un arbre (somme des degrés = 2*n - 2)
    int sommeDegres = 0;
    for (int i = 1; i <= n; ++i) sommeDegres += degres[i];
    qDebug() << "Nombre de sommets:" << n << "| Somme des degrés:" << sommeDegres;

    std::vector<int> resultat;
    std::vector<bool> supprime(n + 1, false);

    for (int k = 0; k < n - 2; k++) {
        int feuille = -1;
        // Chercher la plus petite feuille
        for (int i = 1; i <= n; i++) {
            if (!supprime[i] && degres[i] == 1) {
                feuille = i;
                break;
            }
        }

        if (feuille == -1) {
            qDebug() << "ERREUR : Aucune feuille trouvée à l'itération" << k;
            break;
        }

        // Chercher le voisin
        int voisin = -1;
        for (const Arc& a : g.retournerArcs()) {
            int u = a.retournerSommetDepart().retournerId();
            int v = a.retournerSommetArrivee().retournerId();

            if (u == feuille && !supprime[v]) { voisin = v; break; }
            if (v == feuille && !supprime[u]) { voisin = u; break; }
        }

        qDebug() << "Feuille:" << feuille << "Voisin:" << voisin;

        resultat.push_back(voisin);
        degres[voisin]--;
        degres[feuille] = 0;
        supprime[feuille] = true;
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