#ifndef RECEIVER_H
#define RECEIVER_H

#include <stdio.h>
#include "proc/processor.h"

struct Receiver
{
    FILE *f = nullptr;
};


Stage recOpen(Receiver &rec, const union action::args &args);
Stage recClose(Receiver &rec);
Stage receiveFigure(Receiver &rec, figure &figure);

Stage recFigReadPoints(Receiver &rec, figure &figure);
Stage recFigReadRels(Receiver &rec, figure &figure);

#endif // RECEIVER_H
