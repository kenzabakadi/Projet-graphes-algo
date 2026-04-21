#pragma once
#include"Afficheur.h"
class Graph;
class AfficheurConsole : public Afficheur {
public:
    void afficher(const Graphe& graphe) override;
};
    