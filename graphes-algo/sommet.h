#ifndef SOMMET_H
#define SOMMET_H

#include <string>

class Sommet {
private :
    int id;
    std::string donnees;

public:
    Sommet();
    Sommet(int id, std::string donnees);

    void attribuerId(int id);
    void attribuerDonnees(std::string donnees);

    int retournerId();
    std::string retournerDonnees();
};

#endif // SOMMET_H
