#include "circuitengine.h"

CircuitEngine::CircuitEngine() {}

bool CircuitEngine::setEquation(const QString &equation)
{
    // On coupe juste la chaîne en deux au niveau du "="
    QStringList parts = equation.split("=");
    if (parts.size() != 2) return false;

    m_outputName = parts[0].trimmed();
    m_equation = parts[1].trimmed().toLower(); // On garde tout en minuscule
    return true;
}

// Ces getters sont gardés car le main en a besoin, mais on a viré le reste
QString CircuitEngine::getOutputName() const { return m_outputName; }

int CircuitEngine::evaluate(const QMap<QString, int> &inputs)
{
    return recursiveEvaluate(m_equation, inputs);
}

int CircuitEngine::recursiveEvaluate(QString expr, const QMap<QString, int> &inputs)
{
    expr = expr.trimmed();

    // 1. Gestion des parenthèses (Priorité absolue)
    while (expr.contains("(")) {
        int open = expr.lastIndexOf("(");
        int close = expr.indexOf(")", open);
        if (close == -1) break;

        // On calcule l'intérieur et on remplace par le résultat
        QString sub = expr.mid(open + 1, close - open - 1);
        expr.replace(open, close - open + 1, QString::number(recursiveEvaluate(sub, inputs)));
    }

    // 2. Opérateurs Binaires (OR, XOR, AND)
    // On cherche l'opérateur, on coupe, et on lance la récursion
    int idx;

    if ((idx = expr.lastIndexOf(" or ")) != -1)
        return recursiveEvaluate(expr.left(idx), inputs) || recursiveEvaluate(expr.mid(idx + 4), inputs);

    if ((idx = expr.lastIndexOf(" xor ")) != -1)
        return recursiveEvaluate(expr.left(idx), inputs) ^ recursiveEvaluate(expr.mid(idx + 5), inputs);

    if ((idx = expr.lastIndexOf(" and ")) != -1)
        return recursiveEvaluate(expr.left(idx), inputs) && recursiveEvaluate(expr.mid(idx + 5), inputs);

    // 3. Opérateur Unaire (NOT)
    if (expr.startsWith("not"))
        return !recursiveEvaluate(expr.mid(3), inputs);

    // 4. Valeurs (Variables ou 0/1)
    QString key = expr.toUpper();
    if (key == "1") return 1;
    if (key == "0") return 0;
    return inputs.value(key, 0); // Retourne la valeur de X, Y... ou 0 si inconnu
}
