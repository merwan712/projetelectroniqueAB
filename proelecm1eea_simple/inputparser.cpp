#include "inputparser.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

InputParser::InputParser() {}

bool InputParser::loadSimulationFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur: Impossible d'ouvrir" << filePath;
        return false;
    }

    m_commands.clear();
    QTextStream in(&file);

    // Regex déclarées static pour n'être compilées qu'une seule fois (Optimisation)
    static const QRegularExpression varRegex("^([a-zA-Z]+)\\s*=\\s*([01])$");
    static const QRegularExpression timeRegex("^(\\d+)\\s*ns$");

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        auto varMatch = varRegex.match(line);
        auto timeMatch = timeRegex.match(line);

        if (varMatch.hasMatch()) {
            // On ajoute directement la commande (Variable = Valeur)
            SimCommand cmd;
            cmd.type = "SET_VAR";
            cmd.variableName = varMatch.captured(1).toUpper(); // On met en majuscule pour éviter les erreurs
            cmd.value = varMatch.captured(2).toInt();
            m_commands.append(cmd);
        }
        else if (timeMatch.hasMatch()) {
            // On ajoute directement la commande (Attente)
            SimCommand cmd;
            cmd.type = "WAIT";
            cmd.value = timeMatch.captured(1).toInt();
            m_commands.append(cmd);
        }
    }

    return true;
}

QList<SimCommand> InputParser::getCommands() const
{
    return m_commands;
}

// NOTE : La fonction parseEquation a été supprimée car elle est inutile ici.
// C'est le CircuitEngine qui gère l'équation maintenant.
