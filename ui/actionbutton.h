#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

#include "proc/processor.h"

class ActionButton : public QPushButton
{Q_OBJECT
public:
    ActionButton(QWidget *parent = nullptr);
    void setAction(Action action);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Action action;

signals:
    void act_clicked(Action action);



};

#endif // ACTIONBUTTON_H
