#include <QApplication>
#include "logicsimulator.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);



    a.setStyleSheet("QWidget { background-color: #2D2D30; color: #E0E0E0; font-family: 'Segoe UI'; }"
                    "QLineEdit { background-color: #1E1E1E; color: #00FF00; border: 2px solid #3E3E42; padding: 5px; }");

    logicsimulator fenetre; // creation fenetre
    fenetre.show(); // Affichage

    return a.exec();
}
