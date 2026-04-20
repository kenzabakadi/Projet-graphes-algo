#pragma once
#include "Afficheur.h"
#include <string>

class AfficheurFichier : public Afficheur {
private:
    std::string nomFichier;

public:
    AfficheurFichier(const std::string& nom);

    void afficher(const Graphe& graphe) override;
};

