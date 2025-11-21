#include "chronogramme.h"
#include <QPainter>
#include <QPen>

chronogramme::chronogramme(QWidget *parent)
    : QWidget(parent), X(0), Y(0), Z(0), S(0)
{
    setMinimumSize(400, 200);
}

void chronogramme::setValues(int x, int y, int z, int s)
{
    X = x; Y = y; Z = z; S = s;
    update();
}

void chronogramme::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, 2);
    p.setPen(pen);

    // Entrées
    p.drawText(20, 50, QString("X=%1").arg(X));
    p.drawText(20, 90, QString("Y=%1").arg(Y));
    p.drawText(20, 130, QString("Z=%1").arg(Z));

    // Portes logiques stylisées
    p.drawRect(100, 40, 40, 40);
    p.drawText(115, 65, "AND");

    p.drawRect(160, 80, 40, 40);
    p.drawText(175, 105, "OR");

    p.drawRect(220, 80, 40, 40);
    p.drawText(235, 105, "NOT");

    // Connexions
    p.drawLine(60, 50, 100, 60);   // X vers AND
    p.drawLine(60, 90, 100, 80);   // Y vers AND
    p.drawLine(140, 60, 160, 100); // AND -> OR
    p.drawLine(60, 130, 160, 120); // Z vers OR
    p.drawLine(200, 100, 220, 100);// OR -> NOT
    p.drawLine(260, 100, 320, 100);// NOT -> sortie

    // Sortie
    p.drawText(330, 105, QString("S=%1").arg(S));
}

