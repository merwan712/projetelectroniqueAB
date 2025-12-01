#include "chronogramme.h"
#include <QPainter>

chronogramme::chronogramme(QWidget *parent)
    : QWidget(parent), X(0), Y(0), Z(0), S(0)
{
    // On définit juste une taille minimale
    setMinimumSize(200, 150);
}

void chronogramme::setValues(int x, int y, int z, int s)
{
    // On met à jour les variables
    X = x; Y = y; Z = z; S = s;
    update(); // On redessine
}

void chronogramme::paintEvent(QPaintEvent *) {
    QPainter p(this);

    // 1. Fond simple (Gris foncé pour aller avec le reste)
    p.fillRect(rect(), QColor(45, 45, 48));

    // 2. Texte en blanc
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 12));

    // 3. Affichage uniquement du texte (plus de dessins géométriques)
    int y = 40;
    int ecart = 30;

    p.drawText(20, y,            "X = " + QString::number(X));
    p.drawText(20, y + ecart,    "Y = " + QString::number(Y));
    p.drawText(20, y + ecart*2,  "Z = " + QString::number(Z));

    // Sortie en évidence
    p.setFont(QFont("Arial", 12, QFont::Bold));
    p.drawText(20, y + ecart*3,  "S = " + QString::number(S));
}
