#include "InterfaceGraphique.h"
#include <QApplication>
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    InterfaceGraphique w; // C'est ici que tu appelles ta fenêtre
    w.show();
    return a.exec();
}