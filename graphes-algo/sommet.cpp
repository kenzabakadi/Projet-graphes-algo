#include "sommet.h"

Sommet::Sommet() : id{0}, donnees{""}
{}

Sommet::Sommet(int id, std::string donnees) {
    this->id = id;
    this->donnees = donnees;
}

void Sommet::attribuerId(int id) {
    this->id = id;
}

void Sommet::attribuerDonnees(std::string donnees) {
    this->donnees = donnees;
}

int Sommet::retournerId() const {
    return id;
}

std::string Sommet::retournerDonnees() const{
    return donnees;
}

bool Sommet::operator==(const Sommet& autre) const {
    return id == autre.id;
}