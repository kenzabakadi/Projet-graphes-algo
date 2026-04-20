#include "InterfaceGraphique.h"
#include "ui_interface.h" // Assure-toi que ce fichier est bien généré

InterfaceGraphique::InterfaceGraphique(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this); // C'est cette ligne qui "dessine" ton .ui dans la fenêtre
}