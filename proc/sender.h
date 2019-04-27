#ifndef SENDER_H
#define SENDER_H

#include <stdio.h>
#include "enums.h"
#include "primitives.h"
#include "proc/processor.h"



struct Sender
{
    FILE *f = nullptr;
};


Stage senderOpen(Sender &sender, const union action::args &args);
Stage senderClose(Sender &sender);
Stage sendFigure(const Sender &sender, const figure &figure);

Stage sendFigurePoints(const Sender &sender, const figure &figure);
Stage sendFigureRels(const Sender &sender, const figure &figure);


#endif // SENDER_H
