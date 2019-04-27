#pragma once

#include "ui/coloredled.h"
#include "ui/linecanvas.h"
#include "majorwindow.h"
#include "ui_majorwindow.h"
#include "proc/processor.h"


#include <string.h>
#include <QFileDialog>
#include <QWidget>
#include <QLineEdit>


namespace Ui {
class MajorWindow;
}

class MajorWindow : public QWidget
{Q_OBJECT

public:
    explicit MajorWindow(QWidget *parent = nullptr);
    ~MajorWindow();

private:
    Ui::MajorWindow *ui;
    LineCanvas *canv;

    void setButtonActions();
    void connectButtons();
    void connectColorLeds();

    Stage askDir(char *&str);

    Stage loadInput(action &act);
    Stage load1double(double *args, ColoredLed &led);
    Stage load3doubles(double *args, ColoredLed &led1,
                       ColoredLed &led2, ColoredLed &led3);

    bool is_double(QString &str);



private slots:
    Stage buttonClicked(Action action);
signals:
    void led_setNormalPalette();

};
