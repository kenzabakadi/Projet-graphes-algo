#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "graphe.h" 

class Algorithme {
    protected: 
        Graphe* g; // Pointeur de graphe pour éviter les copies lourdes
    public: 
        Algorithme(Graphe* g);
        virtual ~Algorithme() = default;
        virtual void executer() = 0;
};

#endif // ALGORITHME_H