#include "InterfaceGraphique.h"
#include "ui_interface.h"

InterfaceGraphique::InterfaceGraphique(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::FenetreGraphe)
{
    ui->setupUi(this);
}

InterfaceGraphique::~InterfaceGraphique()
{
    delete ui;
}