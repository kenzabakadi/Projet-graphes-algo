//
// Created by chzoe on 04/04/2026.
//

#include "saisieclavier.h"

SaisieClavier::SaisieClavier(QWidget* parent)
    : m_parent(parent)
{}

void SaisieClavier::saisir(Graphe& graphe)
{
    DialogueSaisieClavier dialogue(graphe, m_parent);
    dialogue.exec();
}