#include "algorithme.h"

Algorithme::Algorithme(Graphe* graphe) : g{graphe} {
    if (!g) {
        throw std::invalid_argument("Graphe nul");
    }
} 