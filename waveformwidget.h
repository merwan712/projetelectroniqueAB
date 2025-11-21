#pragma once
#include <QWidget>
#include <QVector>

class waveformwidget : public QWidget
{
    Q_OBJECT
public:
    explicit waveformwidget(QWidget *parent = nullptr);
    void addValues(int x, int y, int z, int s);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<int> X, Y, Z, S;
};
