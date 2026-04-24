#pragma once
#include "Afficheur.h"
#include <string>

class AfficheurFichier : public Afficheur {
private:
    std::string nomFichier;

public:
    // Ajoute ce constructeur
    AfficheurFichier(const std::string& nom) : nomFichier(nom) {}

    void afficher(const Graphe& graphe) override;
};
