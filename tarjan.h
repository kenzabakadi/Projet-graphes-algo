#ifndef TARJAN_H
#define TARJAN_H

#include "algorithme.h"

class Tarjan : public Algorithme {
    public: 
        Tarjan(Graphe* graphe);
        void executer() override;
}

#endif // TARJAN_H