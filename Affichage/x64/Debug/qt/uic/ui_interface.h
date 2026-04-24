/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenetreGraphe
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frameControles;
    QVBoxLayout *verticalLayout;
    QFrame *ligneSeparation;
    QLabel *titreArcs;
    QComboBox *comboSommetSource;
    QComboBox *comboSommetDestination;
    QLineEdit *inputPoidsArc;
    QPushButton *btnAjouterArc;
    QPushButton *btnModifierArc;
    QPushButton *btnSupprimerArc;
    QComboBox *comboAlgorithme;
    QPushButton *btnLancerAlgorithme;
    QPushButton *pushButton_2;
    QPushButton *btnSaisieClavier;
    QPushButton *btnChargerFichier;
    QPushButton *btnSauvgarderFichier;
    QPushButton *btnSaisieSouris;
    QSpacerItem *espaceVertical;
    QTabWidget *ongletsAffichage;
    QWidget *ongletGraphique;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *zoneDessinGraphe;
    QWidget *ongletListes;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelListeSommets;
    QListWidget *textSommets;
    QLabel *labelListeArcs;
    QListWidget *textArcs;

    void setupUi(QMainWindow *FenetreGraphe)
    {
        if (FenetreGraphe->objectName().isEmpty())
            FenetreGraphe->setObjectName("FenetreGraphe");
        FenetreGraphe->resize(1054, 595);
        centralwidget = new QWidget(FenetreGraphe);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        frameControles = new QFrame(centralwidget);
        frameControles->setObjectName("frameControles");
        frameControles->setMaximumSize(QSize(250, 16777215));
        frameControles->setFrameShape(QFrame::Shape::StyledPanel);
        verticalLayout = new QVBoxLayout(frameControles);
        verticalLayout->setObjectName("verticalLayout");
        ligneSeparation = new QFrame(frameControles);
        ligneSeparation->setObjectName("ligneSeparation");
        ligneSeparation->setFrameShape(QFrame::Shape::HLine);
        ligneSeparation->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(ligneSeparation);

        titreArcs = new QLabel(frameControles);
        titreArcs->setObjectName("titreArcs");
        QFont font;
        font.setBold(true);
        titreArcs->setFont(font);
        titreArcs->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titreArcs);

        comboSommetSource = new QComboBox(frameControles);
        comboSommetSource->setObjectName("comboSommetSource");

        verticalLayout->addWidget(comboSommetSource);

        comboSommetDestination = new QComboBox(frameControles);
        comboSommetDestination->setObjectName("comboSommetDestination");

        verticalLayout->addWidget(comboSommetDestination);

        inputPoidsArc = new QLineEdit(frameControles);
        inputPoidsArc->setObjectName("inputPoidsArc");

        verticalLayout->addWidget(inputPoidsArc);

        btnAjouterArc = new QPushButton(frameControles);
        btnAjouterArc->setObjectName("btnAjouterArc");

        verticalLayout->addWidget(btnAjouterArc);

        btnModifierArc = new QPushButton(frameControles);
        btnModifierArc->setObjectName("btnModifierArc");

        verticalLayout->addWidget(btnModifierArc);

        btnSupprimerArc = new QPushButton(frameControles);
        btnSupprimerArc->setObjectName("btnSupprimerArc");

        verticalLayout->addWidget(btnSupprimerArc);

        comboAlgorithme = new QComboBox(frameControles);
        comboAlgorithme->addItem(QString());
        comboAlgorithme->addItem(QString());
        comboAlgorithme->addItem(QString());
        comboAlgorithme->addItem(QString());
        comboAlgorithme->addItem(QString());
        comboAlgorithme->addItem(QString());
        comboAlgorithme->addItem(QString());
        comboAlgorithme->addItem(QString());
        comboAlgorithme->setObjectName("comboAlgorithme");

        verticalLayout->addWidget(comboAlgorithme);

        btnLancerAlgorithme = new QPushButton(frameControles);
        btnLancerAlgorithme->setObjectName("btnLancerAlgorithme");

        verticalLayout->addWidget(btnLancerAlgorithme);

        pushButton_2 = new QPushButton(frameControles);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        btnSaisieClavier = new QPushButton(frameControles);
        btnSaisieClavier->setObjectName("btnSaisieClavier");

        verticalLayout->addWidget(btnSaisieClavier);

        btnChargerFichier = new QPushButton(frameControles);
        btnChargerFichier->setObjectName("btnChargerFichier");

        verticalLayout->addWidget(btnChargerFichier);

        btnSauvgarderFichier = new QPushButton(frameControles);
        btnSauvgarderFichier->setObjectName("btnSauvgarderFichier");

        verticalLayout->addWidget(btnSauvgarderFichier);

        btnSaisieSouris = new QPushButton(frameControles);
        btnSaisieSouris->setObjectName("btnSaisieSouris");

        verticalLayout->addWidget(btnSaisieSouris);

        espaceVertical = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(espaceVertical);


        horizontalLayout->addWidget(frameControles);

        ongletsAffichage = new QTabWidget(centralwidget);
        ongletsAffichage->setObjectName("ongletsAffichage");
        ongletGraphique = new QWidget();
        ongletGraphique->setObjectName("ongletGraphique");
        verticalLayout_2 = new QVBoxLayout(ongletGraphique);
        verticalLayout_2->setObjectName("verticalLayout_2");
        zoneDessinGraphe = new QGraphicsView(ongletGraphique);
        zoneDessinGraphe->setObjectName("zoneDessinGraphe");

        verticalLayout_2->addWidget(zoneDessinGraphe);

        ongletsAffichage->addTab(ongletGraphique, QString());
        ongletListes = new QWidget();
        ongletListes->setObjectName("ongletListes");
        verticalLayout_3 = new QVBoxLayout(ongletListes);
        verticalLayout_3->setObjectName("verticalLayout_3");
        labelListeSommets = new QLabel(ongletListes);
        labelListeSommets->setObjectName("labelListeSommets");

        verticalLayout_3->addWidget(labelListeSommets);

        textSommets = new QListWidget(ongletListes);
        textSommets->setObjectName("textSommets");

        verticalLayout_3->addWidget(textSommets);

        labelListeArcs = new QLabel(ongletListes);
        labelListeArcs->setObjectName("labelListeArcs");

        verticalLayout_3->addWidget(labelListeArcs);

        textArcs = new QListWidget(ongletListes);
        textArcs->setObjectName("textArcs");

        verticalLayout_3->addWidget(textArcs);

        ongletsAffichage->addTab(ongletListes, QString());

        horizontalLayout->addWidget(ongletsAffichage);

        FenetreGraphe->setCentralWidget(centralwidget);

        retranslateUi(FenetreGraphe);

        ongletsAffichage->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FenetreGraphe);
    } // setupUi

    void retranslateUi(QMainWindow *FenetreGraphe)
    {
        FenetreGraphe->setWindowTitle(QCoreApplication::translate("FenetreGraphe", "\303\211diteur de Graphes", nullptr));
        titreArcs->setText(QCoreApplication::translate("FenetreGraphe", "--- GESTION DES ARCS ---", nullptr));
        comboSommetSource->setPlaceholderText(QCoreApplication::translate("FenetreGraphe", "Sommet d'origine...", nullptr));
        comboSommetDestination->setPlaceholderText(QCoreApplication::translate("FenetreGraphe", "Sommet de destination...", nullptr));
        inputPoidsArc->setPlaceholderText(QCoreApplication::translate("FenetreGraphe", "Poids ou Valeur (optionnel)", nullptr));
        btnAjouterArc->setText(QCoreApplication::translate("FenetreGraphe", "Ajouter Arc", nullptr));
        btnModifierArc->setText(QCoreApplication::translate("FenetreGraphe", "Modifier", nullptr));
        btnSupprimerArc->setText(QCoreApplication::translate("FenetreGraphe", "Supprimer", nullptr));
        comboAlgorithme->setItemText(0, QCoreApplication::translate("FenetreGraphe", "Distance", nullptr));
        comboAlgorithme->setItemText(1, QCoreApplication::translate("FenetreGraphe", "Tarjan", nullptr));
        comboAlgorithme->setItemText(2, QCoreApplication::translate("FenetreGraphe", "Rang", nullptr));
        comboAlgorithme->setItemText(3, QCoreApplication::translate("FenetreGraphe", "Prufer", nullptr));
        comboAlgorithme->setItemText(4, QCoreApplication::translate("FenetreGraphe", "Ordonancement", nullptr));
        comboAlgorithme->setItemText(5, QCoreApplication::translate("FenetreGraphe", "Kruskal", nullptr));
        comboAlgorithme->setItemText(6, QCoreApplication::translate("FenetreGraphe", "Dijkstra", nullptr));
        comboAlgorithme->setItemText(7, QCoreApplication::translate("FenetreGraphe", "Dantzig", nullptr));

        btnLancerAlgorithme->setText(QCoreApplication::translate("FenetreGraphe", "Lancer Algorithme", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FenetreGraphe", "Arreter l'algorithme", nullptr));
        btnSaisieClavier->setText(QCoreApplication::translate("FenetreGraphe", "Saisie clavier", nullptr));
        btnChargerFichier->setText(QCoreApplication::translate("FenetreGraphe", "Charger depuis fichier", nullptr));
        btnSauvgarderFichier->setText(QCoreApplication::translate("FenetreGraphe", "Sauvegarder fichier", nullptr));
        btnSaisieSouris->setText(QCoreApplication::translate("FenetreGraphe", "SaisieSouris", nullptr));
        ongletsAffichage->setTabText(ongletsAffichage->indexOf(ongletGraphique), QCoreApplication::translate("FenetreGraphe", "Vue Graphique Visuelle", nullptr));
        labelListeSommets->setText(QCoreApplication::translate("FenetreGraphe", "Liste des sommets existants :", nullptr));
        labelListeArcs->setText(QCoreApplication::translate("FenetreGraphe", "Liste des arcs existants :", nullptr));
        ongletsAffichage->setTabText(ongletsAffichage->indexOf(ongletListes), QCoreApplication::translate("FenetreGraphe", "Donn\303\251es Brutes (Listes)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FenetreGraphe: public Ui_FenetreGraphe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
