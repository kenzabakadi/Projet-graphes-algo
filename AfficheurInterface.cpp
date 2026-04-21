#include "AfficheurInterface.h"
#include "graphes-algo/graphe.h" // Inclure ton modèle

AfficheurInterface::AfficheurInterface(InterfaceGraphique* interface)
    : interfaceQt(interface) {
}

void AfficheurInterface::afficher(const Graphe& graphe) {
    // Ici, tu appelles les méthodes de ton graphe pour mettre à jour l'interface
    // Exemple : interfaceQt->dessinerGraphe(graphe);
}