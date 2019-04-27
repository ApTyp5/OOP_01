#include "receiver.h"

Stage recOpen(Receiver &rec, const union action::args &args)
{
    rec.f = fopen(args.strArgs, "r");
    return (rec.f == nullptr) ? (Stage::RecOpenError)   :
                                (Stage::AccordingToPlan);
}


Stage recClose(Receiver &rec)
{
    int rc = fclose(rec.f);
    return (rc == 0) ? (Stage::AccordingToPlan) :
                       (Stage::RecCloseError)   ;
}

Stage receiveFigure(Receiver &rec, figure &figure)
{
    Stage rc = recFigReadPoints(rec, figure);

    if (rc == Stage::AccordingToPlan)
    {
        rc = recFigReadRels(rec, figure);
    }

    return rc;
}

Stage recFigReadPoints(Receiver &rec, figure &figure)
{
    Stage rc = Stage::AccordingToPlan;

    size_t num;
    double x, y, z;
    rc = (fscanf(rec.f, "%zui", &num) == 1) ? Stage::AccordingToPlan :
                                              Stage::RecInputError;

    if (rc == Stage::AccordingToPlan && num == 0)
    {
        rc = Stage::RecEmptyInput;
    }
    if (rc == Stage::AccordingToPlan)
    {
        figure.points = new Point3D[num];
        if (figure.points == nullptr)
        {
            rc = Stage::AllocError;
        }
    }
    if (rc == Stage::AccordingToPlan)
    {
        for (size_t i = 0; i < num; i++)
        {
            if ( fscanf(rec.f, "%lf%lf%lf", &x, &y, &z) != 3)
            {
                rc = Stage::RecInputError;
                break;
            }
            (figure.points + i)->x = x;
            (figure.points + i)->y = y;
            (figure.points + i)->z = z;
        }
    }

    if (rc == Stage::AccordingToPlan)
    {
        figure.pointNum = num;
    }

    return rc;
}

Stage recFigReadRels(Receiver &rec, figure &figure)
{
    Stage rc = Stage::AccordingToPlan;

    size_t num;
    size_t pn1, pn2;
    rc = (fscanf(rec.f, "%zui", &num) == 1) ? Stage::AccordingToPlan :
                                              Stage::RecInputError;

    if (rc == Stage::AccordingToPlan && num == 0)
    {
        rc = Stage::RecEmptyInput;
    }
    if (rc == Stage::AccordingToPlan)
    {
        figure.rels = new Relation[num];
        if (figure.rels == nullptr)
        {
            rc = Stage::AllocError;
        }
    }
    if (rc == Stage::AccordingToPlan)
    {
        for (size_t i = 0; i < num; i++)
        {
            if (fscanf(rec.f, "%zui", &pn1) != 1 ||
                fscanf(rec.f, "%zui", &pn2) != 1)
            {
                rc = Stage::RecInputError;
                break;
            }
            (figure.rels + i)->pn1 = pn1;
            (figure.rels + i)->pn2 = pn2;
        }
    }
    if (rc == Stage::AccordingToPlan)
    {
        figure.relNum = num;
    }
    return rc;
}
