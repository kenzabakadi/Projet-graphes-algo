#include "tarjan.h"

Tarjan::Tarjan(Graphe* graphe) : Algorithme(graphe) {}

void Tarjan::executer() {
    g->getFsAps(fs, aps);
}