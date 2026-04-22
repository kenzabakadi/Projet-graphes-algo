// dantzig.h
#ifndef DANTZIG_H
#define DANTZIG_H

#include <limits>
#include "algorithme.h"

class Dantzig : public Algorithme {
    private:
        vector<int> fs;
        vector<int> aps;
        vector<vector<int>> matriceCout;
        bool circuitAbsorbant = false;

        // INFINI/2 pour eviter l'overflow lors des additions
        const int INFINI = std::numeric_limits<int>::max() / 2;

        void recupererFsAps(vector<int>& fs, vector<int>& aps) const;
        vector<vector<int>> construireMatriceCout(int n) const;
        bool dantzig();

    public:
        Dantzig(Graphe& graphe);
        void executer() override;
        bool aCircuitAbsorbant() const;
        const vector<vector<int>>& retournerMatrice() const;
};

#endif // DANTZIG_H
