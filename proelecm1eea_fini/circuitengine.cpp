#include "circuitengine.h"

CircuitEngine::CircuitEngine() {}

bool CircuitEngine::setEquation(const QString &equation)
{
    // On coupe la phrase en deux au niveau du "="
    QStringList parts = equation.split("=");
    if (parts.size() != 2) return false;

    m_outputName = parts[0].trimmed();// On stocke le nom de la sortie (ex: "S")
    m_equation = parts[1].trimmed().toLower();   // On stocke la formule en minuscules
    return true;
}

QString CircuitEngine::getOutputName() const { return m_outputName; }

int CircuitEngine::evaluate(const QMap<QString, int> &inputs)
{
    // On lance le moteur récursif
    return recursiveEvaluate(m_equation, inputs);
}

int CircuitEngine::recursiveEvaluate(QString expr, const QMap<QString, int> &inputs)
{

    expr = expr.trimmed(); // On enlève les espaces au début et à la fin

    // Les Parenthèses
    while (expr.contains("(")) {
        int open = expr.lastIndexOf("(");      // On trouve la dernière parenthèse ouverte
        int close = expr.indexOf(")", open);   // On trouve celle qui la ferme en partant de celle ouverte
        if (close == -1) break;

        // On extrait le texte à l'intérieur
        QString sub = expr.mid(open + 1, close - open - 1);

        // On calcule le résultat de l'intérieur (0 ou 1)
        int subResult = recursiveEvaluate(sub, inputs);

        // On remplace le bloc "(...)" par son résultat dans la phrase
        expr.replace(open, close - open + 1, QString::number(subResult));
    }

    // On cherche les opérateurs pour couper l'équation en deux.

    int idx;

    // On cherche OU
    if ((idx = expr.lastIndexOf(" or ")) != -1)
        // On calcule la partie GAUCHE || On calcule la partie DROITE
        return recursiveEvaluate(expr.left(idx), inputs) || recursiveEvaluate(expr.mid(idx + 4), inputs);

    // On cherche OU exclusif
    if ((idx = expr.lastIndexOf(" xor ")) != -1)
        // Calcul GAUCHE ^ Calcul DROITE
        return recursiveEvaluate(expr.left(idx), inputs) ^ recursiveEvaluate(expr.mid(idx + 5), inputs);

    // On cherche ET
    if ((idx = expr.lastIndexOf(" and ")) != -1)
        // Calcul GAUCHE && Calcul DROITE
        return recursiveEvaluate(expr.left(idx), inputs) && recursiveEvaluate(expr.mid(idx + 5), inputs);

    // On cherche NON
    if (expr.startsWith("not"))
        // On calcule la suite et on inverse le résultat (!)
        return !recursiveEvaluate(expr.mid(3), inputs);


    QString key = expr.toUpper();

    if (key == "1") return 1; // C'est un 1 fixe
    if (key == "0") return 0; // C'est un 0 fixe

    // C'est une variable (X, Y...), on regarde sa valeur actuelle dans la liste
    return inputs.value(key, 0);
}
