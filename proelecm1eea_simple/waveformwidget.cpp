#include "waveformwidget.h"
#include <QPainter>
#include <QPen>

waveformwidget::waveformwidget(QWidget *parent) : QWidget(parent)
{
    // On met un fond blanc pour que ce soit plus joli
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

// C'est cette fonction qu'on a renommée pour corriger ton erreur !
void waveformwidget::addValues(QString signalName, int time, int value)
{
    // On enregistre le point (temps, valeur) dans la liste du signal correspondant
    m_data[signalName].append(QPointF(time, value));

    // On met à jour le temps max (utile si on veut scroller plus tard)
    if (time > m_maxTime) m_maxTime = time;

    // On demande à la fenêtre de se redessiner
    update();
}

void waveformwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 1. Fond Noir (Style Oscilloscope)
    painter.fillRect(rect(), QColor(20, 20, 20)); // Gris très foncé

    // 2. Dessin de la grille (lignes pointillées)
    painter.setPen(QPen(QColor(60, 60, 60), 1, Qt::DashLine));
    for (int i = 0; i < width(); i += 50) painter.drawLine(i, 0, i, height()); // Verticales
    for (int i = 0; i < height(); i += 60) painter.drawLine(0, i, width(), i); // Horizontales

    int ySpacing = 60;
    int index = 0;

    // Palette de couleurs fluo pour les signaux
    QList<QColor> colors = {
        QColor(0, 255, 0),   // Vert Matrix (pour X)
        QColor(0, 255, 255), // Cyan (pour Y)
        QColor(255, 0, 255), // Magenta (pour Z)
        QColor(255, 200, 0)  // Orange (pour S)
    };

    for (auto signalName : m_data.keys()) {
        int baseY = 50 + (index * ySpacing);

        // 3. Nom du signal en Blanc
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 10, QFont::Bold));
        painter.drawText(10, baseY, signalName);

        // 4. La Courbe
        QList<QPointF> points = m_data[signalName];
        if (!points.isEmpty()) {
            // On choisit une couleur différente pour chaque ligne
            QColor curveColor = colors[index % colors.size()];

            // Effet "Glow" (Ombre colorée)
            painter.setPen(QPen(curveColor, 3)); // Ligne plus épaisse

            QPointF lastP = points.first();
            for (const QPointF &currentP : points) {
                double x1 = 50 + lastP.x();
                double y1 = baseY - (lastP.y() * 20);
                double x2 = 50 + currentP.x();
                double y2 = baseY - (currentP.y() * 20);

                painter.drawLine(x1, y1, x2, y1);
                painter.drawLine(x2, y1, x2, y2);
                lastP = currentP;
            }
        }
        index++;
    }
}

void waveformwidget::clear()
{
    m_data.clear();   // On vide la liste des points
    m_maxTime = 200;  // On remet le temps par défaut
    update();         // On efface l'écran
}
