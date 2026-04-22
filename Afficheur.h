#pragma once
class Graphe;

class Afficheur
{
public:
    virtual void afficher(const Graphe& graphe) = 0;
    virtual ~Afficheur() = default; 
};