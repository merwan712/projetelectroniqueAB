#pragma once
#include <QWidget>

class chronogramme : public QWidget {
    Q_OBJECT
public:
    explicit chronogramme(QWidget *parent = nullptr);
    void setValues(int x, int y, int z, int s);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int X, Y, Z, S;
};
