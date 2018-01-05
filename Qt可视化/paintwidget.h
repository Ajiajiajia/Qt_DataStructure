#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0,Qt::WindowFlags f = 0);
    ~PaintWidget();

    void resizeEvent(QResizeEvent *event);

    void paintEvent(QPaintEvent *event);

    QPainter* getPainter();

    void tt();


private:
    QPixmap* mPixmap;
    QPainter* mPainter;
};

#endif // PAINTWIDGET_H
