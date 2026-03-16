#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "algorithme.h"

class Dijkstra : public Algorithme {
    public: 
        Dijkstra(Graphe* graphe);
        void executer() override;
}

#endif // DIJKSTRA_H