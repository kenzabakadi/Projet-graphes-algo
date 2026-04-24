#ifndef DISTANCE_H
#define DISTANCE_H

#include "algorithme.h"

class Distance : public Algorithme {
private:
    vector<int> fs;
    vector<int> aps;
    vector<int> distances;
    int         m_sommetDepart;

    void calculer();

public:
    Distance(Graphe& graphe, int sommetDepart = 1);
    void executer() override;
    vector<int> retournerDistances() const;
};

#endif // DISTANCE_H
