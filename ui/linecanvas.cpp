#include <QPainter>
#include <QWidget>

#include "linecanvas.h"

LineCanvas::LineCanvas(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(Qt::white);
}

void LineCanvas::setProj(const procOutput &output)
{
    proj = output.proj;
    num = output.num;
}

void LineCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();


    if (proj != nullptr && num > 0)
    {
        QPainter painter(this);
        for (size_t i = 0; i < num; i++)
        {
            const Point2D &p1 = proj[i].p1;
            const Point2D &p2 = proj[i].p2;
            QPointF qp1(p1.x + width / 2, p1.y + height / 2);
            QPointF qp2(p2.x + width / 2, p2.y + height / 2);

            painter.drawLine(qp1, qp2);
        }
    }
}

