#ifndef RANG_H
#define RANG_H

#include "algorithme.h"
#include <vector>

class Rang : public Algorithme {
    private : 
        std::vector<int> fs;
        std::vector<int> aps;
        std::vector<int> rangs;

        bool circuit;

        void calculerDdi(std::vector<int>& ddi);

    public : 
        Rang(Graphe& graphe);
        void executer() override;
        std::vector<int> retournerRangs() const;
        bool contientCircuit() const;
};

#endif // RANG_H
