#pragma once
#include"Afficheur.h"
class Graph;
class AfficheurConsole : public Afficheur {
public:
    void Afficher(const Graphe& graphe) override;
};
    