#include "logicsimulator.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitter>

logicsimulator::logicsimulator(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);

    // 1. Barre de texte
    lay->addWidget(m_edit = new QLineEdit("S = (X and Y) or Z"));

    // 2. Schéma et Courbes
    QSplitter *split = new QSplitter(Qt::Vertical);
    split->addWidget(m_schema = new SchematicWidget);
    split->addWidget(m_chrono = new waveformwidget);
    lay->addWidget(split);

    // 3. Bouton
    QPushButton *btn = new QPushButton("Suivant");
    lay->addWidget(btn);

    // 4. Actions
    connect(btn, &QPushButton::clicked, this, &logicsimulator::updateLogic);
    connect(m_edit, &QLineEdit::returnPressed, this, &logicsimulator::updateLogic);

    updateLogic(); // Premier calcul
}

void logicsimulator::updateLogic()
{
    // On met à jour l'équation
    m_schema->setEquation(m_edit->text());
    if (!m_engine.setEquation(m_edit->text())) return;

    // On tire au sort X, Y, Z
    QMap<QString, int> inputs;
    inputs["X"] = rand() % 2;
    inputs["Y"] = rand() % 2;
    inputs["Z"] = rand() % 2;

    // On met à jour les visuels
    m_schema->setInputValues(inputs);

    int S = m_engine.evaluate(inputs);
    m_chrono->addValues("X", m_time, inputs["X"]);
    m_chrono->addValues("Y", m_time, inputs["Y"]);
    m_chrono->addValues("Z", m_time, inputs["Z"]);
    m_chrono->addValues("S", m_time, S);

    m_time += 10;
}
