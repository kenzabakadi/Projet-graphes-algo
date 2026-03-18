#include "tarjan.h"

Tarjan::Tarjan(Graphe* graphe) : Algorithme(graphe) {}

void Tarjan::executer() {
    g->calculerFsAps(fs, aps);
}