#pragma once
#include <QMainWindow>

namespace Ui {
    class FenetreGraphe; // Doit correspondre au nom dans le namespace du fichier ui_interface.h
}

class InterfaceGraphique : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterfaceGraphique(QWidget* parent = nullptr);
    ~InterfaceGraphique();

private:
    Ui::FenetreGraphe* ui;
};