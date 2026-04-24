#include "InterfaceGraphique.h"
#include "graphe.h"
#include "sommet.h"
#include "arc.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    Graphe g(true);

    Sommet s1(1, "Total - 24 Rue d Altkirch");
    Sommet s2(2, "184 Route de Belfort");
    Sommet s3(3, "CORA - 258 Rue de Belfort");
    Sommet s4(4, "170 Rue des Romains");
    Sommet s5(5, "Leclerc - 7 Rue Gay-Lussac");

    g.ajouterSommet(s1);
    g.ajouterSommet(s2);
    g.ajouterSommet(s3);
    g.ajouterSommet(s4);
    g.ajouterSommet(s5);

    g.ajouterArc(Arc(s1, s2, 2));
    g.ajouterArc(Arc(s1, s3, 3));
    g.ajouterArc(Arc(s2, s3, 1));
    g.ajouterArc(Arc(s2, s4, 4));
    g.ajouterArc(Arc(s3, s4, 2));
    g.ajouterArc(Arc(s3, s5, 3));
    g.ajouterArc(Arc(s4, s5, 2));

    InterfaceGraphique w(g);
    w.show();
    return a.exec();
}