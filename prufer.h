#ifndef PRUFER_H
#define PRUFER_H

#include "algorithme.h"
#include <vector>

class Prufer : public Algorithme {
    private : 
        std::vector<int> code;
        std::vector<int> coder();
        void decoder(std::vector<int> code);
    
    public : 
        Prufer(Graphe& graphe);
        void executer() override;
        std::vector<int> retournerCode() const;
        //test
};

#endif // PRUFER_H