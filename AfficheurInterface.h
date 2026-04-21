#pragma once
#include "Afficheur.h"
#include "InterfaceGraphique.h" // Ta classe Qt
#include <memory>

class AfficheurInterface : public Afficheur {
private:
    InterfaceGraphique* interfaceQt; // Pointeur vers ta fenêtre

public:
    AfficheurInterface(InterfaceGraphique* interface);
    void afficher(const Graphe& graphe) override; // Surcharge obligatoire
};