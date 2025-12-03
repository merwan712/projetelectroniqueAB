#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <QString>
#include <QList>

struct SimCommand {
    QString type;        // "SET_VAR" ou "WAIT"
    QString variableName;
    int value;
};

class InputParser
{
public:
    InputParser();

    // On utilise QString et QList (Qt pur)
    bool loadSimulationFile(const QString &filePath);
    QList<SimCommand> getCommands() const;

private:
    QList<SimCommand> m_commands;
};

#endif // INPUTPARSER_H
