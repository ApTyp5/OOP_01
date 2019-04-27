#include "actionbutton.h"

ActionButton::ActionButton(QWidget *parent):
    QPushButton (parent)
{}

void ActionButton::setAction(Action action)
{
    this->action = action;
}

void ActionButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit act_clicked(action);
}
