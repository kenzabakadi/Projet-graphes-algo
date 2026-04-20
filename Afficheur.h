#pragma once
class Graphe;
class Afficheur
{
    virtual void afficheur(const Graphe& graphe) = 0;
    virtual ~Afficheur() = default;
};