#ifndef FENETRERESULTAT_H
#define FENETRERESULTAT_H

#include <QDialog>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "zonedessin.h"
#include "graphe.h"

class FenetreResultat : public QDialog {
    Q_OBJECT
public:
    explicit FenetreResultat(const QString& titre,
        const QString& html,
        Graphe& graphe,
        QWidget* parent = nullptr,
        const std::vector<int>& cheminIds = {},
        const std::vector<std::pair<int, int>>& arcsColories = {});
private:
    QTextBrowser* m_textBrowser;
    ZoneDessin* m_zone;
};

#endif

