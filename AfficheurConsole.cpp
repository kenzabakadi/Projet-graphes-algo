#include"AfficheurConsole.h"
#include<iostream>
#include "graphe.h"
void AfficheurConsole::afficher(const Graphe& graphe)
{
    cout << "==RESEAU DES STATION=="<<endl;
    auto lesSommets = graphe.retournerSommets();
    auto lesArcs = graphe.retournerArcs();
    for (int i = 1;i < lesSommets.size();i++)
    {
        int NommbreArcDei = getfs(getaps[i + 1]) - getfs(getaps[i]) - 1;// ecrire getter pour fs et aps 
            cout << "[Station " << i << "]" << lesSommets[i].stationessence().retourneNom();
        if (getfs(getaps[i]) != 0)
            for (int j = aps[i];j <NommbreArcDei;j++)
            {
                cout << "-> reliée à :Station" << getfs[j] << "(Poids : " << lesArcs[j].retournerPoids() << ")"// a implemnter
            }
        else
            cout << "(Aucun trajet au départ de cette station)";
    }
}