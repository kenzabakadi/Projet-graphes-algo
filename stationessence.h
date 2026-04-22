#ifndef STATIONESSENCE_H
#define STATIONESSENCE_H

#include <string>

class StationEssence {
private :
    std::string nom;
    std::string adresse;
    double x;
    double y;
    double prixSP95;
    double prixSP98;
    double prixGazole;

public:
    StationEssence();
    StationEssence(std::string nom, std::string adresse, double x, double y);

    std::string retournerNom();
    std::string retournerAdresse();
    double retournerX();
    double retournerY();
    double retournerPrixSP95();
    double retournerPrixSP98();
    double retournerPrixGazole();

    void attribuerNom(std::string nom);
    void attribuerAdresse(std::string adresse);
    void attribuerX(double x);
    void attribuerY(double y);
    void attribuerPrixSP95(double prix);
    void attribuerPrixSP98(double prix);
    void attribuerPrixGazole(double prix);
};

#endif // STATIONESSENCE_H
