#ifndef CIRCUITENGINE_H
#define CIRCUITENGINE_H

#include <QString>
#include <QMap>

class CircuitEngine
{
public:
    CircuitEngine();

    bool setEquation(const QString &equation);
    QString getOutputName() const;

    // On utilise QMap (Qt pur)
    int evaluate(const QMap<QString, int> &inputs);

private:
    QString m_outputName;
    QString m_equation;

    int recursiveEvaluate(QString expr, const QMap<QString, int> &inputs);
};

#endif // CIRCUITENGINE_H
