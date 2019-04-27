TEMPLATE = app
QT += widgets gui

FORMS += \
    majorwindow.ui

HEADERS += \
    majorwindow.h \
    ui/linecanvas.h \
    ui/actionbutton.h \
    debug.h \
    defines.h \
    ui/coloredled.h \
    proc/processor.h \
    proc/receiver.h \
    proc/enums.h \
    proc/primitives.h \
    proc/sender.h

SOURCES += \
    majorwindow.cpp \
    ui/linecanvas.cpp \
    ui/actionbutton.cpp \
    main.cpp \
    ui/coloredled.cpp \
    proc/processor.cpp \
    proc/receiver.cpp \
    proc/primitives.cpp \
    proc/sender.cpp
