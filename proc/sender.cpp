#include "sender.h"





Stage senderOpen(Sender &sender, const union action::args &args)
{
    sender.f = fopen(args.strArgs, "w");
    return (sender.f == nullptr) ? (Stage::SenderOpenError) :
                                   (Stage::AccordingToPlan);
}

Stage senderClose(Sender &sender)
{
    int rc = fclose(sender.f);
    return (rc == 0) ? (Stage::AccordingToPlan) :
                       (Stage::SenderCloseError);
}

Stage sendFigure(const Sender &sender, const figure &figure)
{
    Stage rc = sendFigurePoints(sender, figure);

    if (rc == Stage::AccordingToPlan)
    {
        rc = sendFigureRels(sender, figure);
    }

    return rc;
}

Stage sendFigurePoints(const Sender &sender, const figure &figure)
{
    if (figure.pointNum == 0)
    {
        return Stage::SenderEmptyOutput;
    }
    if (figure.points == nullptr)
    {
        return Stage::NullptrReceived;
    }

    Stage rc = (fprintf(sender.f, "%zui\n", figure.pointNum) == 1) ?
                (Stage::AccordingToPlan) : (Stage::SenderOutputError);

    if (rc == Stage::AccordingToPlan)
    {
        for (size_t i = 0; i < figure.pointNum; i++)
        {
            const Point3D &curPoint = *(figure.points + i);
            if ( fprintf(sender.f, "%lf\t%lf\t%lf\n", curPoint.x,
                                                      curPoint.y,
                                                      curPoint.z) != 3)
            {
                rc = Stage::SenderOutputError;
                break;
            }
        }
    }

    return rc;
}

Stage sendFigureRels(const Sender &sender, const figure &figure)
{
    if (figure.relNum == 0)
    {
        return Stage::SenderEmptyOutput;
    }
    if (figure.rels == nullptr)
    {
        return Stage::NullptrReceived;
    }

    Stage rc = (fprintf(sender.f, "%zui\n", figure.pointNum) == 1) ?
                (Stage::AccordingToPlan) : (Stage::SenderOutputError);

    if (rc == Stage::AccordingToPlan)
    {
        for (size_t i = 0; i < figure.pointNum; i++)
        {
            const Point3D &curPoint = *(figure.points + i);
            if ( fprintf(sender.f, "%lf\t%lf\t%lf\n", curPoint.x,
                                                      curPoint.y,
                                                      curPoint.z) != 3)
            {
                rc = Stage::SenderOutputError;
                break;
            }
        }
    }

    return rc;
}
