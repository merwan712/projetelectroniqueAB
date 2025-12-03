#include "inputparser.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

InputParser::InputParser() {}

// Fonction principale : Lit le fichier texte et remplit la liste de commandes
bool InputParser::loadSimulationFile(const QString &filePath)
{

    QFile file(filePath); //Ouverture du fichier

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur: Impossible d'ouvrir" << filePath;
        return false; // Échec
    }


    m_commands.clear(); // On vide la liste précédente
    QTextStream in(&file); // Création du flux pour lire ligne



    //  var  cherche des lettres, un égal, et 0 ou 1 (Groupe 2)
    static const QRegularExpression varRegex("^([a-zA-Z]+)\\s*=\\s*([01])$");

    // cherche des chiffres suivis de ns
    static const QRegularExpression timeRegex("^(\\d+)\\s*ns$");


    while (!in.atEnd()) {

        QString line = in.readLine().trimmed();// Lecture de la ligne et suppression des espaces inutiles au début/fin (.trimmed)


        if (line.isEmpty()) continue;// si la ligne est vide on passe


        auto varMatch = varRegex.match(line);   // une affectation (X=1) ?
        auto timeMatch = timeRegex.match(line); // une attente (100ns) ?

        // variable
        if (varMatch.hasMatch()) {
            SimCommand cmd;
            cmd.type = "SET_VAR";

            // On capture le nom et on met en maj
            cmd.variableName = varMatch.captured(1).toUpper();

            // On capture la val et on convertit le texte 1 en entier
            cmd.value = varMatch.captured(2).toInt();

            // On ajoute
            m_commands.append(cmd);
        }
        //temps
        else if (timeMatch.hasMatch()) {
            SimCommand cmd;
            cmd.type = "WAIT";


            cmd.value = timeMatch.captured(1).toInt(); // On capture le nombre

            m_commands.append(cmd); // On ajoute
        }

    }

    file.close();
    return true;
}


QList<SimCommand> InputParser::getCommands() const
{
    return m_commands;
}
