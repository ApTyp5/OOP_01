#ifndef LINECANVAS_H
#define LINECANVAS_H

#include <QWidget>
#include <QPaintEvent>

#include "proc/processor.h"



class LineCanvas : public QWidget
{Q_OBJECT
public:
    explicit LineCanvas(QWidget *parent = nullptr);
    void setProj(const procOutput &lst);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const Line2D *proj = nullptr;
    size_t num = 0;
};

#endif // LINECANVAS_H
