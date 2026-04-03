//
// Created by chzoe on 18/03/2026.
//

#ifndef PROJET_GRAPHES_ALGO_SAISIE_H
#define PROJET_GRAPHES_ALGO_SAISIE_H

#include "graphe.h"

class Saisie {
public:
    virtual void saisir(Graphe& graphe) = 0;
    virtual ~Saisie() = default;
};

#endif //PROJET_GRAPHES_ALGO_SAISIE_H