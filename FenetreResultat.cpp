#include "FenetreResultat.h"

FenetreResultat::FenetreResultat(const QString& titre,
    const QString& html,
    Graphe& graphe,
    QWidget* parent,
    const std::vector<int>& cheminIds,
    const std::vector<std::pair<int, int>>& arcsColories)
    : QDialog(parent)
{
    setWindowTitle(titre);
    setMinimumSize(1100, 600);

    // Layout gauche : tableau + bouton fermer
    QVBoxLayout* layoutGauche = new QVBoxLayout;
    m_textBrowser = new QTextBrowser(this);
    m_textBrowser->setHtml(html);
    m_textBrowser->setMinimumWidth(450);
    layoutGauche->addWidget(m_textBrowser);

    QPushButton* btnFermer = new QPushButton("Fermer", this);
    connect(btnFermer, &QPushButton::clicked, this, &QDialog::accept);
    layoutGauche->addWidget(btnFermer);

    // Layout droite : graphe visuel
    m_zone = new ZoneDessin(graphe.estOriente(), this);
    m_zone->setMinimumWidth(500);
    m_zone->chargerDepuisGraphe(graphe);
    m_zone->setSommetsEnSurbrillance(cheminIds);
    m_zone->setArcsColories(arcsColories);

    // Layout principal
    QHBoxLayout* layoutPrincipal = new QHBoxLayout(this);
    layoutPrincipal->addLayout(layoutGauche);
    layoutPrincipal->addWidget(m_zone);
}