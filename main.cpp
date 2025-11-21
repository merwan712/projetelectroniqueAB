// main.cpp
#include <QApplication>
#include "logicsimulator.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(NULL)); // initialisation du générateur aléatoire

    logicsimulator sim;
    sim.show();

    return app.exec();
}
