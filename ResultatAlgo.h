#ifndef RESULTATALGO_H
#define RESULTATALGO_H

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

class ResultatAlgo : public QDialog {
    Q_OBJECT
public:
    // On passe le titre et le texte à afficher
    ResultatAlgo(const QString& titre, const QString& texte, QWidget* parent = nullptr);
};

#endif