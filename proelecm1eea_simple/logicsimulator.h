#ifndef LOGICSIMULATOR_H
#define LOGICSIMULATOR_H

#include <QWidget>
#include <QLineEdit>
#include "schematicwidget.h"
#include "waveformwidget.h"
#include "circuitengine.h"

class logicsimulator : public QWidget {
    Q_OBJECT
public:
    explicit logicsimulator(QWidget *parent = nullptr);
    void updateLogic(); // Fonction unique de mise à jour

private:
    SchematicWidget *m_schema;
    waveformwidget *m_chrono;
    QLineEdit *m_edit;
    CircuitEngine m_engine;
    int m_time = 0;
};

#endif
