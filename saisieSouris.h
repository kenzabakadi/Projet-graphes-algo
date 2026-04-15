#ifndef SAISISOURIS_H
#define SAISISOURIS_H

#include "saisie.h"
#include <QWidget>


class SaisieSouris : public Saisie {
public:
    explicit SaisieSouris(QWidget* parent = nullptr);
    void saisir(Graphe& graphe) override;

private:
    QWidget* m_parent;
};

#endif // SAISISOURIS_H
