#include "waveformwidget.h"
#include <QPainter>

waveformwidget::waveformwidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400, 200);
}

void waveformwidget::addValues(int x, int y, int z, int s) {
    X.append(x);
    Y.append(y);
    Z.append(z);
    S.append(s);
    update();
}

void waveformwidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::black);

    int w = width();
    int step = w / qMax(1, X.size());

    auto drawSignal = [&](const QVector<int> &sig, int yBase, const QString &name) {
        p.drawText(5, yBase - 5, name);
        for (int i = 1; i < sig.size(); ++i) {
            int y1 = yBase - sig[i - 1] * 20;
            int y2 = yBase - sig[i] * 20;
            p.drawLine((i - 1) * step, y1, i * step, y1);
            p.drawLine(i * step, y1, i * step, y2);
        }
    };

    drawSignal(X, 40, "X");
    drawSignal(Y, 80, "Y");
    drawSignal(Z, 120, "Z");
    drawSignal(S, 160, "S");
}
