#include "ResultatAlgo.h"

ResultatAlgo::ResultatAlgo(const QString& titre, const QString& texte, QWidget* parent)
    : QDialog(parent) {

    setWindowTitle(titre);
    resize(400, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QTextEdit* zoneTexte = new QTextEdit(this);
    zoneTexte->setPlainText(texte);
    zoneTexte->setReadOnly(true); // L'utilisateur ne peut pas modifier le résultat

    QPushButton* btnFermer = new QPushButton("Fermer", this);
    connect(btnFermer, &QPushButton::clicked, this, &ResultatAlgo::accept);

    layout->addWidget(zoneTexte);
    layout->addWidget(btnFermer);
}