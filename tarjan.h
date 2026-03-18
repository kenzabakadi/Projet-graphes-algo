#ifndef TARJAN_H
#define TARJAN_H

#include "algorithme.h"

class Tarjan : public Algorithme {
    private: 
        vector<int> fs;
        vector<int> aps;
    public: 
        Tarjan(Graphe* graphe);
        void executer() override;
};

#endif // TARJAN_H