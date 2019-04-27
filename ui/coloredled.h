#ifndef COLOREDLED_H
#define COLOREDLED_H

#include <QLineEdit>

class ColoredLed : public QLineEdit
{Q_OBJECT
public:
    ColoredLed(QWidget *parent = nullptr);
public slots:
    void setErrorPalette();
    void setNormalPalette();
};

#endif // COLOREDLED_H
