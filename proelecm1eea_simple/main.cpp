#include <QApplication>
#include <QSplitter>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QMap>

#include "schematicwidget.h"
#include "waveformwidget.h"
#include "inputparser.h"
#include "circuitengine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Style Dark Mode
    a.setStyleSheet("QWidget { background-color: #2D2D30; color: #E0E0E0; font-family: 'Segoe UI'; }"
                    "QLineEdit { background-color: #1E1E1E; color: #00FF00; border: 2px solid #3E3E42; padding: 5px; }");

    QWidget *mainWidget = new QWidget;
    mainWidget->resize(1000, 800);
    QVBoxLayout *layout = new QVBoxLayout(mainWidget);

    QLineEdit *inputBar = new QLineEdit();
    inputBar->setText("S = (X and Y) or not Z");
    layout->addWidget(inputBar);

    QSplitter *splitter = new QSplitter(Qt::Vertical);
    layout->addWidget(splitter);

    SchematicWidget *schema = new SchematicWidget(splitter);
    waveformwidget *chrono = new waveformwidget(splitter);
    splitter->addWidget(schema);
    splitter->addWidget(chrono);

    CircuitEngine engine;
    InputParser parser;
    QString filename = "simulation.txt";

    // Fonction de simulation "Instantanée"
    auto runSimulation = [&]() {
        QString userEquation = inputBar->text();

        schema->setEquation(userEquation);
        if (!engine.setEquation(userEquation)) return;

        chrono->clear();

        if (parser.loadSimulationFile(filename)) {
            int currentTime = 0;
            QMap<QString, int> inputs;
            inputs["X"] = 0; inputs["Y"] = 0; inputs["Z"] = 0;

            // --- C'EST ICI QUE CA SE JOUE ---
            // On donne les valeurs initiales au schéma pour qu'il affiche des 0 partout
            schema->setInputValues(inputs);

            // Point initial Chrono
            int valS = engine.evaluate(inputs);
            chrono->addValues("X", 0, inputs["X"]);
            chrono->addValues("Y", 0, inputs["Y"]);
            chrono->addValues("Z", 0, inputs["Z"]);
            chrono->addValues("S", 0, valS);

            for (const SimCommand &cmd : parser.getCommands()) {
                if (cmd.type == "SET_VAR") {
                    inputs[cmd.variableName] = cmd.value;
                } else if (cmd.type == "WAIT") {
                    currentTime += cmd.value;
                }

                valS = engine.evaluate(inputs);

                chrono->addValues("X", currentTime, inputs["X"]);
                chrono->addValues("Y", currentTime, inputs["Y"]);
                chrono->addValues("Z", currentTime, inputs["Z"]);
                chrono->addValues("S", currentTime, valS);

                // À la fin de la boucle, 'inputs' contient les dernières valeurs du fichier
                // C'est ce que le schéma affichera
                schema->setInputValues(inputs);
            }
        }
    };

    QObject::connect(inputBar, &QLineEdit::returnPressed, runSimulation);
    runSimulation();

    mainWidget->show();
    return a.exec();
}
