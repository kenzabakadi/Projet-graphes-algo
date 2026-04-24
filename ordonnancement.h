#ifndef ORDONNANCEMENT_H
#define ORDONNANCEMENT_H

#include "algorithme.h"
#include <map>

class Ordonnancement : public Algorithme {
private:
    vector<int> fs;
    vector<int> aps;
    vector<int> datesPlusTot;
    vector<int> fpc;   
    vector<int> appc;
    std::map<int, int> m_durees;

    void calculer();

public:
    Ordonnancement(Graphe& graphe);
    void executer() override;
    vector<int> retournerDatesPlusTot() const;
    void setDurees(const std::map<int, int>& durees) { m_durees = durees; }
};

#endif // ORDONNANCEMENT_H
