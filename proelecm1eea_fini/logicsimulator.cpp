#include "logicsimulator.h"
#include <QVBoxLayout>
#include <QSplitter>
#include <QMap>

logicsimulator::logicsimulator(QWidget *parent) : QWidget(parent)
{
    resize(1000, 800);
    setWindowTitle("Simulateur Logique Modulaire");

    // --- 1. Construction de l'Interface ---
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_inputBar = new QLineEdit("S = (X and Y) or not Z");
    layout->addWidget(m_inputBar);

    QSplitter *splitter = new QSplitter(Qt::Vertical);
    layout->addWidget(splitter);

    m_schema = new SchematicWidget(splitter);
    m_chrono = new waveformwidget(splitter);
    splitter->addWidget(m_schema);
    splitter->addWidget(m_chrono);


    //  L'interface envoie un signal, le contrôleur agit.
    connect(m_inputBar, &QLineEdit::returnPressed, this, &logicsimulator::runSimulation);

    // Lancement initial
    runSimulation();
}

void logicsimulator::runSimulation()
{
    QString eq = m_inputBar->text(); // on recupere le texte ecrit

    // 1. On configure les modules indépendamment
    m_schema->setEquation(eq);       // Mise à jour visuelle
    if (!m_engine.setEquation(eq)) return; // Mise à jour logique

    m_chrono->clear();

    // boucle de simulation

    if (m_parser.loadSimulationFile("simulation.txt")) {
        int currentTime = 0; //intialisation temps
        QMap<QString, int> inputs;
        inputs["X"] = 0; inputs["Y"] = 0; inputs["Z"] = 0; //initialisation variable

        // Fonction locale pour éviter la répétition
        auto updateStep = [&]() {
            int valS = m_engine.evaluate(inputs);// calcul sortie

            // On envoie les données
            m_chrono->addValues("X", currentTime, inputs["X"]);
            m_chrono->addValues("Y", currentTime, inputs["Y"]);
            m_chrono->addValues("Z", currentTime, inputs["Z"]);
            m_chrono->addValues("S", currentTime, valS);

            m_schema->setInputValues(inputs); // envoie donnees au schema
        };

        // etat initial
        updateStep();

        // Boucle sur le fichier
        for (const SimCommand &cmd : m_parser.getCommands()) {
            if (cmd.type == "SET_VAR") //changement variable
            {
                inputs[cmd.variableName] = cmd.value;
            }
            else if (cmd.type == "WAIT")// avance temps
            {
                currentTime += cmd.value;
            }
            updateStep();
        }
    }
}
