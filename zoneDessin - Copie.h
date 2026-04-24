#ifndef ZONEDESSIN_H
#define ZONEDESSIN_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QInputDialog>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPoint>
#include <vector>
#include <QString>

#include "graphe.h"
#include "sommet.h"
#include "arc.h"
#include "stationessence.h"

class ZoneDessin : public QWidget
{
    Q_OBJECT

public:
    struct ArcVisuel {
        int idDepart;
        int idArrivee;
        int poids;
    };
    enum Mode { ModeSommet, ModeArc, ModeEffacer };

    explicit ZoneDessin(bool oriente, QWidget* parent = nullptr);
    void chargerDepuisGraphe(const Graphe& g);

    void setMode(Mode mode);
    void setOriente(bool oriente);
    void setAvecStations(bool avecStations);
    bool avecStations() const { return m_avecStations; }
    void reinitialiser();
    bool confirmer(Graphe& graphe) const;
    void ajouterArcDeLExterieur(int idDepart, int idArrivee, int poids);
    int getPoidsArc(int index) const;
    void supprimerArcVisuel(int index);
    ArcVisuel getArc(int index) const;
    void modifierPoidsVisuel(int index, int nouveauPoids);
    void effacerSommetParId(int id);
    int nbArcs() const;
    void setSommetsEnSurbrillance(const std::vector<int>& ids);
    void setArcsColories(const std::vector<std::pair<int, int>>& arcs);
    void reinitialiserCouleurs();

signals:
    void sommetAjouteSignal(int id, QString nom,QPoint pos);
    void arcCliqueSignal(int index); 
    void arcDeselectionneSignal();
    void arcModifieSignal(int idDep, int idArr, int ancienPoids, int nouveauPoids);
    void demanderSuppressionSommetSignal(int idSommet);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    struct SommetVisuel {
        int     id;
        QString nom;
        QPoint  pos;
        bool    estStation = false;
        QString adresse;
        double  coordX = 0, coordY = 0;
        double  prixSP95 = -1, prixSP98 = -1, prixGazole = -1;
    };

   

    bool m_oriente;
    bool m_avecStations;
    Mode m_mode;
    std::vector<SommetVisuel> m_sommets;
    std::vector<ArcVisuel>m_arcs;
    int m_prochainId;
    int m_departSelectionne;

    static constexpr int RAYON = 20;
    static constexpr double RAYON_CLIC_ARC = 7.0;

    // Detection
    int    sommetSous(const QPoint& pos) const;
    int    arcSous(const QPoint& pos) const;

    // Actions
    void   placerSommet(const QPoint& pos);
    void   placerStation(const QPoint& pos);
    void   gererClicArc(const QPoint& pos);
    void   effacerSommet(const QPoint& pos);
    void   modifierPoidsArc(int indexArc);
    bool   dialogueStation(SommetVisuel& sv) const;

    // Dessin
    void   dessinerSommet(QPainter& p, const SommetVisuel& s, bool surbrillance) const;
    void   dessinerArc(QPainter& p, const ArcVisuel& a, bool surbrillance) const;
    void   dessinerFleche(QPainter& p, QPoint dep, QPoint arr) const;

    // Geometrie
    QPoint pointSurBord(QPoint centre, QPoint vers) const;
    static double distancePointSegment(QPoint pt, QPoint a, QPoint b);
    std::vector<int> m_sommetsEnSurbrillance;
    std::vector<std::pair<int, int>> m_arcsColories;
};

#endif // ZONEDESSIN_H
