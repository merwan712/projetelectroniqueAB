#pragma once
#include <QWidget>
#include "chronogramme.h"
#include "waveformwidget.h"

class QPushButton;

class logicsimulator : public QWidget {
    Q_OBJECT
public:
    explicit logicsimulator(QWidget *parent = nullptr);

private slots:
    void nextStep();

private:
    int X, Y, Z;
    chronogramme *chronoView;
    waveformwidget *waveView;
    QPushButton *btnStep;

    void updateCircuit();
};
