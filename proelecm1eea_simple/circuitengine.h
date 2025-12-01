#ifndef CIRCUITENGINE_H
#define CIRCUITENGINE_H

#include <QString>
#include <QMap>
#include <QList>
#include <QStringList>

class CircuitEngine
{
public:
    CircuitEngine();

    // Définit l'équation à analyser (ex: "S = (A and B) or C")
    bool setEquation(const QString &equation);

    // Calcule la sortie en fonction des entrées (ex: X=1, Y=0...)
    int evaluate(const QMap<QString, int> &inputs);

    // Retourne la liste des portes trouvées pour le dessin (ex: "AND", "OR")
    QStringList getDetectedGates() const;

    // Retourne le nom de la variable de sortie (ex: "S")
    QString getOutputName() const;

    // Retourne la liste des variables d'entrées trouvées (ex: "X", "Y", "Z")
    QStringList getInputNames() const;

private:
    QString m_equation;
    QString m_outputName;
    QStringList m_inputNames;
    QStringList m_gates;

    // Fonction interne pour l'évaluation récursive
    int recursiveEvaluate(QString expr, const QMap<QString, int> &inputs);
};

#endif // CIRCUITENGINE_H
