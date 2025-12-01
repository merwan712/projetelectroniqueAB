#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Structure pour stocker une commande de simulation (ex: X=1 ou TEMPS=100ns)
struct SimCommand {
    QString type;  // "SET_VAR" ou "WAIT"
    QString variableName;
    int value;     // 0 ou 1 pour une variable, durée en ns pour WAIT
};

class InputParser
{
public:
    InputParser();

    // Lit le fichier de test fourni par l'utilisateur
    bool loadSimulationFile(const QString &filePath);

    // Récupère la liste des commandes lues
    QList<SimCommand> getCommands() const;

    // Analyse une équation (ex: S = A and B) -> Préparation pour LogicSimulator
    bool parseEquation(const QString &equation);

private:
    QList<SimCommand> m_commands;
};

#endif // INPUTPARSER_H
