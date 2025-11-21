// logicsimulator.cpp
#include "logicsimulator.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <cstdlib>
#include <ctime>
#include <random>

logicsimulator::logicsimulator(QWidget *parent)
    : QWidget(parent), X(0), Y(0), Z(0)
{
    setWindowTitle("Logic Circuit Simulator");
    resize(600, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);

    chronoView = new chronogramme;
    waveView = new waveformwidget;
    btnStep = new QPushButton("Étape suivante");

    layout->addWidget(chronoView);
    layout->addWidget(btnStep);
    layout->addWidget(waveView);

    connect(btnStep, &QPushButton::clicked, this, &logicsimulator::nextStep);

    updateCircuit();
}

void logicsimulator::nextStep()
{
    // Générateur aléatoire moderne
    static std::random_device rd;  // source de vraie entropie
    static std::mt19937 gen(rd()); // générateur Mersenne Twister
    static std::uniform_int_distribution<> dist(0, 1); // 0 ou 1

    X = dist(gen);
    Y = dist(gen);
    Z = dist(gen);

    updateCircuit();
}


void logicsimulator::updateCircuit()
{
    int S = !((X && Y) || Z);
    chronoView->setValues(X, Y, Z, S);
    waveView->addValues(X, Y, Z, S);

    // Forcer la mise à jour graphique
    chronoView->update();
    waveView->update();
}
