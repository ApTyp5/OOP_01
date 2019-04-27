#include "coloredled.h"

ColoredLed::ColoredLed(QWidget *parent):
    QLineEdit (parent)
{
    setNormalPalette();
}

void ColoredLed::setErrorPalette()
{
    setPalette(Qt::red);
}

void ColoredLed::setNormalPalette()
{
    setPalette(Qt::white);
}
