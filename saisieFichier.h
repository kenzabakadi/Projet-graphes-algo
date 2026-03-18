//
// Created by chzoe on 18/03/2026.
//

#ifndef PROJET_GRAPHES_ALGO_SAISIEFICHIER_H
#define PROJET_GRAPHES_ALGO_SAISIEFICHIER_H

#include "saisie.h"
#include <string>

class SaisieFichier : public Saisie {
private:
    std::string nomFichier;

public:
    SaisieFichier(const std::string& nom);
    void saisir(Graphe& graphe) override;
};

#endif //PROJET_GRAPHES_ALGO_SAISIEFICHIER_H