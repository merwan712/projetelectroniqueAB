#ifndef SCHEMATICWIDGET_H
#define SCHEMATICWIDGET_H

#include <QWidget>
#include <QString>
#include <QMap>
#include <QPair> // Pour renvoyer (Position + Valeur)

class SchematicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SchematicWidget(QWidget *parent = nullptr);

    void setEquation(QString equation);

    // NOUVEAU : On envoie les valeurs actuelles (ex: X=1, Y=0) pour l'affichage
    void setInputValues(QMap<QString, int> values);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_equation;
    QMap<QString, int> m_currentValues; // Stocke l'état actuel (0 ou 1)

    // La fonction retourne maintenant une PAIRE : {Position du point, Valeur Logique (0 ou 1)}
    QPair<QPoint, int> drawRecursive(QPainter &painter, QString expr, int x, int y, int heightStep);

    int findMainOperator(const QString &expr, QString &opType);

    // Petite fonction pour dessiner le carré "0" ou "1"
    void drawLogicLabel(QPainter &painter, int x, int y, int value);
    int countLeaves(QString expr);
};

#endif // SCHEMATICWIDGET_H
