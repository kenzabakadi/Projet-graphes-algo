#ifndef ARC_H
#define ARC_H

#include "sommet.h"

class Arc {
private :
    int poids;
    Sommet depart;
    Sommet arrivee;

public:
    Arc();
    Arc(Sommet depart, Sommet arrivee, int poids);

    void attribuerPoids(int poids);
    void attribuerSommetDepart(Sommet depart);
    void attribuerSommetArrivee(Sommet arrivee);

    int retournerPoids();
    Sommet retournerSommetDepart();
    Sommet retournerSommetArrivee();

    bool operator==(const Arc& autre) const;
};

#endif // ARC_H
