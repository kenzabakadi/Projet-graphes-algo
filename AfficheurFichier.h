#pragma once
#include "Afficheur.h"
#include <string>

class AfficheurFichier : public Afficheur {
private:
    std::string nomFichier;

public:
    void afficher(const Graphe& graphe) override;
};

