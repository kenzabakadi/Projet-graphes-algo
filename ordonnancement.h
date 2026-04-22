#ifndef ORDONNANCEMENT_H
#define ORDONNANCEMENT_H

#include "algorithme.h"

class Ordonnancement : public Algorithme {
private:
    vector<int> fs;
    vector<int> aps;
    vector<int> datesPlusTot;
    vector<int> fpc;   
    vector<int> appc;  

    void calculer();

public:
    Ordonnancement(Graphe& graphe);
    void executer() override;
    vector<int> retournerDatesPlusTot() const;
};

#endif // ORDONNANCEMENT_H
