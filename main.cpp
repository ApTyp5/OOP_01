#include <QApplication>
#include <QDesktopWidget>

#include "defines.h"
#include "majorwindow.h"



int main(int ac, char **av)
{
    QApplication app(ac, av);
    MajorWindow majorWindow;
/*
    majorWindow.setFixedSize(
                app.desktop()->width(),
                app.desktop()->height() - FRAME_HEIGHT);
//*/
    majorWindow.show();
    return app.exec();
}
