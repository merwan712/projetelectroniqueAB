#ifndef LOGICSIMULATOR_H
#define LOGICSIMULATOR_H

#include <QWidget>
#include <QLineEdit>

// Inclusion des classes nécessaires
#include "schematicwidget.h"
#include "waveformwidget.h"
#include "circuitengine.h"
#include "inputparser.h"

class logicsimulator : public QWidget
{
    Q_OBJECT // Indispensable pour les signaux/slots

public:
    explicit logicsimulator(QWidget *parent = nullptr);

public slots:
    // C'est la fonction que le bouton et la barre de texte appellent
    void runSimulation();

private:
    // --- LES WIDGETS (Interface) ---
    // Il faut les déclarer ici pour qu'ils soient connus partout dans la classe
    QLineEdit *m_inputBar;
    SchematicWidget *m_schema;
    waveformwidget *m_chrono;

    // --- LA LOGIQUE (Moteur) ---
    CircuitEngine m_engine;
    InputParser m_parser;
};

#endif // LOGICSIMULATOR_H
