#ifndef WAVEFORMWIDGET_H   // <--- CORRECTION 1 : Garde de début
#define WAVEFORMWIDGET_H   // <--- CORRECTION 1 : Garde de début

#include <QWidget>
#include <QPaintEvent>
#include <QMap>
#include <QList>
#include <QPointF>

class waveformwidget : public QWidget { // (J'ai gardé ton nom en minuscule)
    Q_OBJECT
public:
    explicit waveformwidget(QWidget *parent = nullptr);

    // CORRECTION 2 : J'ai renommé 'addPoint' en 'addValues'
    // pour que ton logicSimulator soit content !
    void addValues(QString signalName, int time, int value);
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, QList<QPointF>> m_data;
    int m_maxTime = 200;
};

#endif // WAVEFORMWIDGET_H  <--- CORRECTION 1 : Garde de fin (Indispensable !)
