#include "rang.h"

Rang::Rang(Graphe& graphe) : Algorithme(graphe), circuit(false) {}

void Rang::executer() {
    g.calculerFsAps(fs,aps);
    int nombreSommets = aps[0];

    std::vector<int> ddi;
    calculerDdi(ddi);

    rangs.assign(nombreSommets + 1, nombreSommets);

    std::vector<int> sommetsRangActuel, sommetsRangSuivant;

    for(int i = 1; i <= nombreSommets; i++)
    {
        if(ddi[i]==0) 
        {
            sommetsRangActuel.push_back(i);
            rangs[i] = 0;
        }
    }

    int rangCourant = 1;
    while(!sommetsRangActuel.empty()) 
    {
        sommetsRangSuivant.clear();
        for(int i : sommetsRangActuel) {
            for(int j = aps[i]; fs[j] != 0; j++) {
                int sommetSuccesseur = fs[j];
                ddi[sommetSuccesseur] --;
                if(ddi[sommetSuccesseur] == 0) {
                    rangs[sommetSuccesseur] = rangCourant;
                    sommetsRangSuivant.push_back(sommetSuccesseur);
                }
            }
        }
        sommetsRangActuel = sommetsRangSuivant;
        rangCourant++;
    }

    circuit = false;
    for(int i = 1; i <= nombreSommets; i++) {
        if(rangs[i] == nombreSommets) {
            circuit = true;
            break;
        }
    }
 
}

void Rang::calculerDdi(std::vector<int>& ddi) {
    int nombreSommets = aps[0];
    ddi.assign(nombreSommets + 1, 0);

    for(int i = 1; i < fs.size(); i++) {
        int sommetSuccesseur = fs[i];
        if(sommetSuccesseur > 0) {
            ddi[sommetSuccesseur] ++;
        }
    }
}

std::vector<int> Rang::retournerRangs() const {
    return rangs;
}

bool Rang::contientCircuit() const {
    return circuit;
}