#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "algorithme.h"
#include <vector>

class Kruskal : public Algorithme {
    public:
        struct Arete {
            int    s;
            int    t;
            double poids;
        };
        Kruskal(Graphe& graphe);
        void executer() override;

        // Accès aux résultats
        const std::vector<Arete>& retournerArbre()   const;
        int                       retournerPoidsTotal() const;
private:



    // Résultat
    std::vector<Arete> m_arbre;

    // Gestion des composantes connexes
    std::vector<int> m_prem;
    std::vector<int> m_pilch;
    std::vector<int> m_cfc;
    std::vector<int> m_nbElem;

    // Étapes de l'algorithme
    std::vector<Arete> construireAretes() const;
    void               trier(std::vector<Arete>& aretes) const;
    void               initialiserComposantes(int n);
    void               fusionner(int i, int j);
    void               kruskal(std::vector<Arete>& aretes, int n);
};

#endif // KRUSKAL_H
