#include "stationessence.h"

StationEssence::StationEssence() : x(0), y(0), prixSP95(-1), prixSP98(-1), prixGazole(-1) {}

StationEssence::StationEssence(std::string nom, std::string adresse, double x, double y) {
    this->nom = nom;
    this->adresse = adresse;
    this->x = x;
    this->y = y;
    this->prixSP95 = -1;
    this->prixSP98 = -1;
    this->prixGazole = -1;
}

std::string StationEssence::retournerNom() {
    return nom;
}

std::string StationEssence::retournerAdresse() {
    return adresse;
}

double StationEssence::retournerX() {
    return x;
}

double StationEssence::retournerY() {
    return y;
}

double StationEssence::retournerPrixSP95() {
    return prixSP95;
}

double StationEssence::retournerPrixSP98() {
    return prixSP98;
}

double StationEssence::retournerPrixGazole() {
    return prixGazole;
}

void StationEssence::attribuerNom(std::string nom) {
    this->nom = nom;
}

void StationEssence::attribuerAdresse(std::string adresse) {
    this->adresse = adresse;
}

void StationEssence::attribuerX(double x) {
    this->x = x;
}

void StationEssence::attribuerY(double y) {
    this->y = y;
}

void StationEssence::attribuerPrixSP95(double prix) {
    this->prixSP95 = prix;
}

void StationEssence::attribuerPrixSP98(double prix) {
    this->prixSP98 = prix;
}

void StationEssence::attribuerPrixGazole(double prix) {
    this->prixGazole = prix;
}
