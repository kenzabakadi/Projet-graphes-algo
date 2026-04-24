//
// Created by chzoe on 04/04/2026.
//

#ifndef PROJET_GRAPHES_ALGO_SAISIECLAVIER_H
#define PROJET_GRAPHES_ALGO_SAISIECLAVIER_H

#include "saisie.h"
#include "dialoguesaisieclavier.h"
#include <QWidget>


class SaisieClavier : public Saisie
{
    public:
        explicit SaisieClavier(QWidget* parent = nullptr);
        void saisir(Graphe& graphe) override;

    private:
        QWidget* m_parent;
};

#endif //PROJET_GRAPHES_ALGO_SAISIECLAVIER_H