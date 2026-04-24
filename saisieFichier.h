#ifndef SAISIEFICHIER_H
#define SAISIEFICHIER_H

#include "saisie.h"
#include "sommet.h"
#include <string>
#include <vector>
#include <fstream>

class SaisieFichier : public Saisie {
    private:
        std::string nomFichier;

        bool ouvrirFichier(std::ifstream& fichier) const;
        void lireSommets(std::ifstream& fichier, Graphe& graphe, std::vector<Sommet>& listeSommets, int n) const;
        void lireArcs(std::ifstream& fichier, Graphe& graphe, std::vector<Sommet>& listeSommets, int n, int m, bool oriente) const;

    public:
        SaisieFichier(const std::string& nom);
        void saisir(Graphe& graphe) override;
};

#endif // SAISIEFICHIER_H