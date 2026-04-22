#include "zonedessin.h"
#include <QPen>
#include <QBrush>
#include <QFont>
#include <cmath>

// Constructeur

ZoneDessin::ZoneDessin(bool oriente, QWidget* parent)
    : QWidget(parent)
    , m_oriente(oriente)
    , m_mode(ModeSommet)
    , m_avecStations(false)
    , m_prochainId(1)
    , m_departSelectionne(-1)
{
    setMinimumSize(600, 400);
    setMouseTracking(true);
    setCursor(Qt::CrossCursor);
    setStyleSheet("background-color: #2e1e1e; border: 1px solid #444;");
}

// Setters publics

void ZoneDessin::setMode(Mode mode)
{
    m_mode = mode;
    m_departSelectionne = -1;
    switch (mode) {
    case ModeSommet:  setCursor(Qt::CrossCursor);         break;
    case ModeArc:     setCursor(Qt::PointingHandCursor);  break;
    case ModeEffacer: setCursor(Qt::ForbiddenCursor);     break;
    }
    update();
}

void ZoneDessin::setOriente(bool oriente)
{
    m_oriente = oriente;
    update();
}

void ZoneDessin::setAvecStations(bool avecStations)
{
    if (m_avecStations == avecStations) return;

    if (!m_sommets.empty()) {
        auto rep = QMessageBox::question(
            this, "Réinitialiser ?",
            "Changer ce paramètre va effacer le graphe en cours.\nContinuer ?",
            QMessageBox::Yes | QMessageBox::No);
        if (rep != QMessageBox::Yes) {
            return;
        }
    }
    m_avecStations = avecStations;
    reinitialiser();
}

void ZoneDessin::reinitialiser()
{
    m_sommets.clear();
    m_arcs.clear();
    m_prochainId = 1;
    m_departSelectionne = -1;
    update();
}

// Transfert vers le Graphe

bool ZoneDessin::confirmer(Graphe& graphe) const
{
    if (m_sommets.empty()) {
        QMessageBox::warning(const_cast<ZoneDessin*>(this),
                             "Graphe vide", "Aucun sommet dessine.");
        return false;
    }

    for (const SommetVisuel& sv : m_sommets)
        graphe.ajouterSommet(Sommet(sv.id, sv.nom.toStdString()));

    std::vector<Sommet> listeSommets;
    for (const SommetVisuel& sv : m_sommets)
        listeSommets.emplace_back(sv.id, sv.nom.toStdString());

    auto trouver = [&](int id) -> Sommet {
        for (const Sommet& s : listeSommets)
            if (s.retournerId() == id) return s;
        return Sommet();
    };

    for (const ArcVisuel& av : m_arcs)
        graphe.ajouterArc(Arc(trouver(av.idDepart), trouver(av.idArrivee), av.poids));

    return true;
}

// Evenements souris

void ZoneDessin::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) return;
    QPoint pos = event->pos();

    // 1. Logique de sélection exclusive d'arc
    int index = arcSous(pos);
    if (index != -1) {
        emit arcCliqueSignal(index);
        return; // On arrête tout, on ne dessine rien par-dessus
    }
    else {
        // On a cliqué dans le vide, on désélectionne
        emit arcDeselectionneSignal();
    }

    // 2. Le switch existant pour les actions de dessin
    switch (m_mode) {
    case ModeSommet:
        if (m_avecStations) placerStation(pos);
        else                placerSommet(pos);
        break;
    case ModeArc:
        gererClicArc(pos);
        break;
    case ModeEffacer:
        effacerSommet(pos);
        break;
    }
}

void ZoneDessin::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) return;
    QPoint pos = event->pos();

    // Priorité 1 : sommet
    int idSommet = sommetSous(pos);
    if (idSommet != -1) {
        emit demanderSuppressionSommetSignal(idSommet);
        return;
    }

    // Priorité 2 : arc
    int idx = arcSous(pos);
    if (idx != -1)
        modifierPoidsArc(idx);
}

// Actions

void ZoneDessin::placerSommet(const QPoint& pos)
{
    if (sommetSous(pos) != -1) return;

    bool ok;
    QString nom = QInputDialog::getText(
        this, "Nouveau sommet",
        QString("Nom du sommet %1 :").arg(m_prochainId),
        QLineEdit::Normal, QString("S%1").arg(m_prochainId), &ok);
    if (!ok || nom.trimmed().isEmpty()) return;

    SommetVisuel sv;
    sv.id  = m_prochainId++;
    sv.nom = nom.trimmed();
    sv.pos = pos;
    m_sommets.push_back(sv);
    emit sommetAjouteSignal(sv.id, sv.nom, sv.pos);
    update();

}

void ZoneDessin::placerStation(const QPoint& pos)
{
    if (sommetSous(pos) != -1) return;

    SommetVisuel sv;
    sv.id        = m_prochainId;
    sv.pos       = pos;
    sv.estStation = true;

    if (!dialogueStation(sv)) return;

    m_prochainId++;
    m_sommets.push_back(sv);
    update();
}

bool ZoneDessin::dialogueStation(SommetVisuel& sv) const
{
    QDialog dlg(const_cast<ZoneDessin*>(this));
    dlg.setWindowTitle(QString("Station-essence – sommet %1").arg(sv.id));
    dlg.setMinimumWidth(360);

    QFormLayout* form = new QFormLayout(&dlg);
    form->setSpacing(8);
    form->setContentsMargins(12, 12, 12, 8);

    // Champs
    QLineEdit* edNom     = new QLineEdit(sv.nom.isEmpty()
                                         ? QString("Station %1").arg(sv.id) : sv.nom);
    QLineEdit* edAdresse = new QLineEdit(sv.adresse);
    QDoubleSpinBox* spX  = new QDoubleSpinBox; spX->setRange(-180, 180);  spX->setDecimals(6); spX->setValue(sv.coordX);
    QDoubleSpinBox* spY  = new QDoubleSpinBox; spY->setRange(-90,  90);   spY->setDecimals(6); spY->setValue(sv.coordY);
    QDoubleSpinBox* sp95 = new QDoubleSpinBox; sp95->setRange(-1, 9.99); sp95->setDecimals(3); sp95->setValue(sv.prixSP95);  sp95->setSpecialValueText("Non disponible");
    QDoubleSpinBox* sp98 = new QDoubleSpinBox; sp98->setRange(-1, 9.99); sp98->setDecimals(3); sp98->setValue(sv.prixSP98);  sp98->setSpecialValueText("Non disponible");
    QDoubleSpinBox* spGaz= new QDoubleSpinBox; spGaz->setRange(-1, 9.99);spGaz->setDecimals(3);spGaz->setValue(sv.prixGazole);spGaz->setSpecialValueText("Non disponible");

    sp95->setSingleStep(0.001);
    sp98->setSingleStep(0.001);
    spGaz->setSingleStep(0.001);

    form->addRow("Nom :",          edNom);
    form->addRow("Adresse :",      edAdresse);
    form->addRow("Longitude (x) :", spX);
    form->addRow("Latitude (y) :",  spY);
    form->addRow("Prix SP95 (€/L) :", sp95);
    form->addRow("Prix SP98 (€/L) :", sp98);
    form->addRow("Prix Gazole (€/L) :", spGaz);

    QDialogButtonBox* btns = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
    form->addRow(btns);

    QObject::connect(btns, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(btns, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    if (dlg.exec() != QDialog::Accepted) return false;

    if (edNom->text().trimmed().isEmpty()) {
        QMessageBox::warning(const_cast<ZoneDessin*>(this),
                             "Erreur", "Le nom de la station ne peut pas etre vide.");
        return false;
    }

    sv.nom       = edNom->text().trimmed();
    sv.adresse   = edAdresse->text().trimmed();
    sv.coordX    = spX->value();
    sv.coordY    = spY->value();
    sv.prixSP95  = sp95->value();
    sv.prixSP98  = sp98->value();
    sv.prixGazole= spGaz->value();
    return true;
}

void ZoneDessin::gererClicArc(const QPoint& pos)
{
    int idClique = sommetSous(pos);
    if (idClique == -1) return;

    if (m_departSelectionne == -1) {
        m_departSelectionne = idClique;
        update();
        return;
    }

    int idDepart  = m_departSelectionne;
    int idArrivee = idClique;
    m_departSelectionne = -1;


    // Pas de doublon
    for (const ArcVisuel& a : m_arcs) {
        if (a.idDepart == idDepart && a.idArrivee == idArrivee) {
            QMessageBox::warning(this, "Arc invalide", QString("L'arc %1 -> %2 existe deja.").arg(idDepart).arg(idArrivee));
            update();
            return;
        }
    }

    bool ok;
    int poids = QInputDialog::getInt(
        this, "Poids de l'arc",
        QString("Poids de l'arc %1 -> %2 :").arg(idDepart).arg(idArrivee), 1, -9999, 9999, 1, &ok);
    if (!ok) { update(); return; }

    m_arcs.push_back({ idDepart, idArrivee, poids });
    update();
}

void ZoneDessin::effacerSommet(const QPoint& pos)
{
    int id = sommetSous(pos);
    if (id == -1) return;
    effacerSommetParId(id);
}

void ZoneDessin::modifierPoidsArc(int indexArc)
{
    ArcVisuel& a = m_arcs[indexArc];
    int ancienPoids = a.poids;

    bool ok;
    int nouveauPoids = QInputDialog::getInt(this, "Modifier le poids",
        QString("Nouveau poids de %1 -> %2 :").arg(a.idDepart).arg(a.idArrivee),
        a.poids, -9999, 9999, 1, &ok);

    if (ok) {
        a.poids = nouveauPoids; // ← mise à jour visuelle directe
        update();
        emit arcModifieSignal(a.idDepart, a.idArrivee, ancienPoids, nouveauPoids);
        // ← plus de a.poids = nouveauPoids ni de update() ici
    }
}

// Dessin

void ZoneDessin::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.fillRect(rect(), QColor(46, 30, 30));

    // Legende du mode courant
    p.setPen(QColor(170, 170, 170));
    p.setFont(QFont("Courier New", 9));
    QString modeTxt;
    switch (m_mode) {
    case ModeSommet:
        modeTxt = "Mode : sommet  |  Clic = placer un sommet";
        break;
    case ModeArc:
        modeTxt = (m_departSelectionne == -1)
                      ? "Mode : arc  |  Clic sur le sommet de depart"
                      : "Mode : arc  |  Clic sur le sommet d'arrivee";
        break;
    case ModeEffacer:
        modeTxt = "Mode : effacer  |  Clic sur un sommet pour le supprimer";
        break;
    }
    p.drawText(8, 16, modeTxt);
    p.setPen(QColor(120, 120, 120));
    p.drawText(8, 30, "Double-clic sur un arc pour modifier son poids");

    // Arcs
    for (const ArcVisuel& a : m_arcs)
        dessinerArc(p, a, false);

    // Sommets
    for (const SommetVisuel& s : m_sommets)
        dessinerSommet(p, s, s.id == m_departSelectionne);
}

void ZoneDessin::dessinerSommet(QPainter& p, const SommetVisuel& s, bool surbrillance) const
{
    QColor couleurBord, couleurFond, couleurTexte;

    if (s.estStation) {
        couleurBord  = surbrillance ? QColor(255, 200,  50) : QColor(255, 160,  50);
        couleurFond  = surbrillance ? QColor( 80,  40,   0) : QColor( 60,  30,   0);
        couleurTexte = surbrillance ? QColor(255, 200,  50) : QColor(255, 210, 150);
    } else {
        couleurBord  = surbrillance ? QColor(241,  15,  15) : QColor(250, 137, 137);
        couleurFond  = surbrillance ? QColor( 61,   0,   0) : QColor( 46,  30,  30);
        couleurTexte = surbrillance ? QColor(241,  15,  15) : QColor(244, 205, 205);
    }

    p.setPen(QPen(couleurBord, surbrillance ? 3 : 2));
    p.setBrush(couleurFond);
    p.drawEllipse(s.pos, RAYON, RAYON);

    // ID au centre
    p.setPen(couleurTexte);
    p.setFont(QFont("Courier New", 9, QFont::Bold));
    QRect rectId(s.pos.x() - RAYON, s.pos.y() - RAYON, RAYON * 2, RAYON * 2);
    p.drawText(rectId, Qt::AlignCenter, QString::number(s.id));

    // Nom en dessous
    p.setFont(QFont("Courier New", 8));
    p.setPen(QColor(200, 166, 166));
    QRect rectNom(s.pos.x() - 50, s.pos.y() + RAYON + 2, 100, 16);
    p.drawText(rectNom, Qt::AlignCenter, s.nom);

    if (s.estStation) {
        p.setPen(QColor(255, 160, 50));
        p.setFont(QFont("Courier New", 7));
        QRect rectIcon(s.pos.x() - 50, s.pos.y() + RAYON + 14, 100, 12);
    }
}

void ZoneDessin::dessinerArc(QPainter& p, const ArcVisuel& a,bool /*surbrillance*/) const
{
    bool trouve = false;
    QPoint dep, arr;
    for (const SommetVisuel& s : m_sommets) {
        if (s.id == a.idDepart) { dep = s.pos; trouve = true; }
        if (s.id == a.idArrivee) arr = s.pos;
    }
    if (!trouve) {
        // C'est ici que ça coince !
        qDebug() << "Arc non dessiné : Sommet de départ ID" << a.idDepart << "introuvable dans m_sommets";
        return;
    }

    p.setPen(QPen(QColor(227, 192, 161), 2));
    p.setBrush(Qt::NoBrush);

    if (dep == arr)
    {
        int r = 20;
        QRect loopRect(dep.x() - r, dep.y() - 2 * r, 2 * r, 2 * r);
        p.drawEllipse(loopRect);

        if (m_oriente)
        {
            QPoint ptAvant(dep.x() + r+2, dep.y()-21);
            QPoint ptFin(dep.x() + r-3, dep.y()-11);
            dessinerFleche(p, ptAvant, ptFin);
        }

        p.setPen(QColor(243, 139, 168));
        p.setFont(QFont("Courier New", 8, QFont::Bold));
        p.drawText(dep.x() + r, dep.y() - r-10, QString::number(a.poids));
    }
    else
    {
        QPoint ptDep = pointSurBord(dep, arr);
        QPoint ptArr = pointSurBord(arr, dep);

        p.drawLine(ptDep, ptArr);

        if (m_oriente)
            dessinerFleche(p, ptDep, ptArr);

        QPoint milieu((ptDep.x() + ptArr.x()) / 2, (ptDep.y() + ptArr.y()) / 2);
        p.setPen(QColor(243, 139, 168));
        p.setFont(QFont("Courier New", 8, QFont::Bold));
        p.drawText(milieu.x() + 4, milieu.y() - 4, QString::number(a.poids));
    }
}


void ZoneDessin::dessinerFleche(QPainter& p, QPoint dep, QPoint arr) const
{
    // Direction dep -> arr
    double dx = arr.x() - dep.x();
    double dy = arr.y() - dep.y();
    double dist = std::sqrt(dx*dx + dy*dy);
    if (dist < 1.0) return;

    double angle = std::atan2(dy, dx);

    const double longueur  = 13.0;
    const double ouverture = 0.42;

    QPoint p1(
        arr.x() - static_cast<int>(longueur * std::cos(angle - ouverture)),
        arr.y() - static_cast<int>(longueur * std::sin(angle - ouverture))
        );
    QPoint p2(
        arr.x() - static_cast<int>(longueur * std::cos(angle + ouverture)),
        arr.y() - static_cast<int>(longueur * std::sin(angle + ouverture))
        );

    p.setPen(QPen(QColor(227, 198, 161), 1));
    p.setBrush(QColor(227, 198, 161));
    QPolygon fleche;
    fleche << arr << p1 << p2;
    p.drawPolygon(fleche);
}

// Geometrie

QPoint ZoneDessin::pointSurBord(QPoint centre, QPoint vers) const
{
    double dx = vers.x() - centre.x();
    double dy = vers.y() - centre.y();
    double dist = std::sqrt(dx*dx + dy*dy);
    if (dist < 1.0) return centre;
    return QPoint(
        centre.x() + static_cast<int>(RAYON * dx / dist),
        centre.y() + static_cast<int>(RAYON * dy / dist)
        );
}

double ZoneDessin::distancePointSegment(QPoint pt, QPoint a, QPoint b)
{
    double dx = b.x() - a.x();
    double dy = b.y() - a.y();
    double len2 = dx*dx + dy*dy;
    if (len2 < 1.0) return std::hypot(pt.x()-a.x(), pt.y()-a.y());

    double t = ((pt.x()-a.x())*dx + (pt.y()-a.y())*dy) / len2;
    t = std::max(0.0, std::min(1.0, t));
    double projX = a.x() + t*dx;
    double projY = a.y() + t*dy;
    return std::hypot(pt.x()-projX, pt.y()-projY);
}

// Detection

int ZoneDessin::sommetSous(const QPoint& pos) const
{
    for (const SommetVisuel& s : m_sommets) {
        int dx = pos.x() - s.pos.x();
        int dy = pos.y() - s.pos.y();
        if (dx*dx + dy*dy <= RAYON*RAYON)
            return s.id;
    }
    return -1;
}

int ZoneDessin::arcSous(const QPoint& pos) const
{
    for (int i = 0; i < static_cast<int>(m_arcs.size()); ++i) {
        const ArcVisuel& a = m_arcs[i];
        QPoint dep, arr;
        for (const SommetVisuel& s : m_sommets) {
            if (s.id == a.idDepart)  dep = s.pos;
            if (s.id == a.idArrivee) arr = s.pos;
        }
        QPoint ptDep = pointSurBord(dep, arr);
        QPoint ptArr = pointSurBord(arr, dep);

        if (distancePointSegment(pos, ptDep, ptArr) <= RAYON_CLIC_ARC)
            return i;
    }
    return -1;
}
//chargement dessin depuis un graphe 
void ZoneDessin::chargerDepuisGraphe(const Graphe& g) {
    m_sommets.clear();
    m_arcs.clear();
    m_prochainId = 1;

    // Convertir les sommets du Graphe en SommetVisuel
    for (const Sommet& s : g.retournerSommets()) {
        SommetVisuel sv;
        sv.id = s.retournerId();
        sv.nom = QString::fromStdString(s.retournerDonnees());

        double angle = 2.0 * 3.14159 * (sv.id - 1) / g.retournerSommets().size();
        sv.pos = QPoint(300 + 150 * std::cos(angle), 200 + 100 * std::sin(angle));

        m_sommets.push_back(sv);
        if (sv.id >= m_prochainId) m_prochainId = sv.id + 1;
    }

    // Convertir les arcs du Graphe en ArcVisuel
    for (const Arc& a : g.retournerArcs()) {
        int idDep = a.retournerSommetDepart().retournerId();
        int idArr = a.retournerSommetArrivee().retournerId();

        // Si non-orienté, ignorer l'arc inverse pour ne pas afficher en double
        if (!g.estOriente() && idDep > idArr) continue;

        m_arcs.push_back({ idDep, idArr, a.retournerPoids() });
    }

    update();
}
void ZoneDessin::ajouterArcDeLExterieur(int idDepart, int idArrivee, int poids) {
    // 1. Vérification de sécurité pour éviter les doublons
    for (const ArcVisuel& a : m_arcs) {
        if (a.idDepart == idDepart && a.idArrivee == idArrivee) {
            return; // L'arc existe déjà
        }
    }

    // 2. Ajout au vecteur interne
    m_arcs.push_back({ idDepart, idArrivee, poids });
    qDebug() << "Arc ajouté ! Nombre total d'arcs dans la zone :" << m_arcs.size();

    // 3. Rafraîchissement de l'affichage
    update();
}
ZoneDessin::ArcVisuel ZoneDessin::getArc(int index) const {
    return m_arcs[index];
}
int ZoneDessin::getPoidsArc(int index) const {
    if (index >= 0 && index < static_cast<int>(m_arcs.size())) {
        return m_arcs[index].poids;
    }
    return 0;
}



void ZoneDessin::supprimerArcVisuel(int index) {
    if (index >= 0 && index < static_cast<int>(m_arcs.size())) {
        m_arcs.erase(m_arcs.begin() + index);
        update(); // Important pour voir l'arc disparaître !
    }
}
void ZoneDessin::modifierPoidsVisuel(int index, int nouveauPoids) {
    if (index >= 0 && index < static_cast<int>(m_arcs.size())) {
        m_arcs[index].poids = nouveauPoids;
        update();
    }
}

void ZoneDessin::effacerSommetParId(int id) {
    // Supprimer le sommet de la liste des sommets
    m_sommets.erase(std::remove_if(m_sommets.begin(), m_sommets.end(),
        [id](const SommetVisuel& s) { return s.id == id; }), m_sommets.end());

    // Supprimer tous les arcs connectés à ce sommet
    m_arcs.erase(std::remove_if(m_arcs.begin(), m_arcs.end(),
        [id](const ArcVisuel& a) { return a.idDepart == id || a.idArrivee == id; }),
        m_arcs.end());

    update(); // Rafraîchir l'affichage
}
int ZoneDessin::nbArcs() const { return static_cast<int>(m_arcs.size()); }