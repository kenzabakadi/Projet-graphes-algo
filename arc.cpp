#include "arc.h"

Arc::Arc() : poids(0) {}

Arc::Arc(Sommet depart, Sommet arrivee, int poids) {
    this->depart = depart;
    this->arrivee = arrivee;
    this->poids = poids;
}

void Arc::attribuerPoids(int poids) {
    this->poids = poids;
}

void Arc::attribuerSommetDepart(Sommet depart) {
    this->depart = depart;
}

void Arc::attribuerSommetArrivee(Sommet arrivee) {
    this->arrivee = arrivee;
}

int Arc::retournerPoids() const {
    return poids;
}

Sommet Arc::retournerSommetDepart() const {
    return depart;
}

Sommet Arc::retournerSommetArrivee() const {
    return arrivee;
}

bool Arc::operator==(const Arc& autre) const {
    return depart == autre.depart && arrivee == autre.arrivee && poids == autre.poids;
}