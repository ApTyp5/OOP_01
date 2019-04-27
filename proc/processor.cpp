#include "processor.h"
#include "primitives.h"
#include "receiver.h"
#include "sender.h"

Stage proc_action(procOutput &out, const action &action)
{
    static struct figure figure;
    static struct veiwer veiwer;

    Stage stage = Stage::AccordingToPlan;

    switch (action.type)
    {
    case(Action::Load):
        stage = proc_load(figure, action.args);
        break;
    case(Action::Save):
        stage = proc_save(figure, action.args);
        break;
    case(Action::Move):
        stage = proc_move(figure, action.args);
        break;
    case(Action::Scale):
    case(Action::Rotate):
        stage = proc_transform(figure, action);
        break;
    case(Action::Project):
        stage = proc_make_projection(out, figure, veiwer);
        break;
    }

    return stage;
}

Stage proc_load(figure &figure, const union action::args &args)
{
    Stage rc = Stage::AccordingToPlan;
    Receiver rec;
    struct figure newFigure;


    rc = recOpen(rec, args);
    if (rc == Stage::AccordingToPlan)
    {
        rc = receiveFigure(rec, newFigure);
    }

    recClose(rec);

    if (rc == Stage::AccordingToPlan)
    {
        if (figure.points)
        {
            delete [] figure.points;
        }
        figure.points = newFigure.points;
        figure.pointNum = newFigure.pointNum;

        if (figure.rels)
        {
            delete [] figure.rels;
        }
        figure.rels = newFigure.rels;
        figure.relNum = newFigure.relNum;

        figure.is_init = true;
    }

    return rc;
}

Stage proc_save(figure &figure, const union action::args &action)
{
    Stage rc = Stage::AccordingToPlan;
    Sender sender;

    rc = senderOpen(sender, action);
    if (rc == Stage::AccordingToPlan)
    {
        rc = sendFigure(sender, figure);
    }

    senderClose(sender);

    return rc;
}

Stage proc_move(figure &figure, const union action::args &action)
{
    Stage rc = (figure.is_init == true) ? Stage::AccordingToPlan :
                                          Stage::FigureUnInit;

    if (rc == Stage::AccordingToPlan)
    {
        for (size_t i = 0; i < figure.pointNum; i++)
        {
            rc = point_move( *(figure.points + i), action.dArgs );
            if (rc != Stage::AccordingToPlan)
            {
                break;
            }
        }
    }

    return rc;
}

Stage proc_scale(figure &figure, const union action::args &action)
{
    Stage rc = (figure.is_init == true) ? Stage::AccordingToPlan :
                                          Stage::FigureUnInit;

    if (rc == Stage::AccordingToPlan)
    {
        for (size_t i = 0; i < figure.pointNum; i++)
        {
            rc = point_scale( *(figure.points + i), action.dArgs );
            if (rc != Stage::AccordingToPlan)
            {
                break;
            }
        }
    }
    return Stage::AccordingToPlan;
}

Stage proc_rotate(figure &figure, const union action::args &action)
{
    Stage rc =  (figure.is_init == true) ? (Stage::AccordingToPlan) :
                                           (Stage::FigureUnInit)    ;
    if (rc == Stage::AccordingToPlan)
    {
        for (size_t i = 0; i < figure.pointNum; i++)
        {
            rc = point_rotate( *(figure.points + i), action.dArgs );
            if (rc != Stage::AccordingToPlan)
            {
                break;
            }
        }
    }

    return rc;
}

// eye (0, 0, 0)
// plain (0, 0, 10)
Stage proc_make_projection(procOutput &out, const figure &figure,
                           const veiwer &veiwer)
{
    if (figure.is_init == false)
    {
        return Stage::FigureUnInit;
    }

    Stage rc = Stage::AccordingToPlan;

    out.proj = new Line2D[figure.relNum];
    if (out.proj == nullptr)
    {
        rc = Stage::AllocError;
    }

    if (rc == Stage::AccordingToPlan)
    {
        for (size_t i = 0; i < figure.relNum; i++)
        {
            Point3D &p1 = *(figure.points + (figure.rels + i)->pn1);
            Point3D &p2 = *(figure.points + (figure.rels + i)->pn2);

            Point2D &outP1 = (out.proj + i)->p1;
            Point2D &outP2 = (out.proj + i)->p2;

            rc = makeXProj(outP1.x, veiwer, p1);
            if (rc != Stage::AccordingToPlan) break;

            rc = makeYProj(outP1.y, veiwer, p1);
            if (rc != Stage::AccordingToPlan) break;

            rc = makeXProj(outP2.x, veiwer, p2);
            if (rc != Stage::AccordingToPlan) break;

            rc = makeYProj(outP2.y, veiwer, p2);
            if (rc != Stage::AccordingToPlan) break;
        }
    }

    if (rc == Stage::AccordingToPlan)
    {
        out.num = figure.relNum;
    }

    return rc;
}


Stage makeXProj(double &answer, const veiwer &veiwer, const Point3D &point)
{
    const Point3D &eye = veiwer.eye;
    if ( fabs(eye.z - point.z) < 1e-5)
    {
        return Stage::ZeroDiv;
    }

    answer = (eye.z - veiwer.zp) * (point.x - eye.x) / (eye.z - point.z) - eye.x;
    return Stage::AccordingToPlan;
}

Stage makeYProj(double &answer, const veiwer &veiwer, const Point3D &point)
{
    const Point3D &eye = veiwer.eye;
    if (fabs(eye.z - point.z) < 1e-5)
    {
        return Stage::ZeroDiv;
    }

    answer = (eye.z - veiwer.zp) * (point.y - eye.y) / (eye.z - point.z) - eye.y;
    return Stage::AccordingToPlan;
}



// Трансформация фигуры с переносом в центр (масштабирование, вращение)
Stage proc_transform(figure &figure, const action &action)
{
    struct action addMoveAction;
    Stage rc = act_fig_center_init(addMoveAction.args, figure.pointNum, figure.points);

    if (rc == Stage::AccordingToPlan)
    {
        rc = proc_move(figure, addMoveAction.args);
        act_revert(addMoveAction.args);
    }

    if (rc == Stage::AccordingToPlan)
    {
        switch (action.type)
        {
        case (Action::Scale):
            rc = proc_scale(figure, action.args);
            break;
        case (Action::Rotate):
            rc = proc_rotate(figure, action.args);
            break;
        default:
            rc = Stage::IncorrectAction;
        }
    }

    if (rc == Stage::AccordingToPlan)
    {
        rc = proc_move(figure, addMoveAction.args);
    }

    return rc;
}

Stage act_fig_center_init(union action::args &args, size_t pnum, Point3D *points)
{
    if (points == nullptr)
    {
        return Stage::NullptrReceived;
    }
    if (pnum == 0)
    {/* В конце мы делим на pnum */
        return Stage::ZeroDiv;
    }

    double sumX = 0, sumY = 0, sumZ = 0;

    for (size_t i = 0; i < pnum; i++)
    {
        sumX += (points + i)->x;
        sumY += (points + i)->y;
        sumZ += (points + i)->z;
    }

    *(args.dArgs + 0) = -(sumX / pnum);
    *(args.dArgs + 1) = -(sumY / pnum);
    *(args.dArgs + 2) = -(sumZ / pnum);

    return Stage::AccordingToPlan;
}

Stage act_revert(union action::args &args)
{
    if (args.dArgs + 1 == nullptr || args.dArgs + 2 == nullptr)
    {
        return Stage::NullptrReceived;
    }
    for (int i = 0; i < 3; i++)
    {
        *(args.dArgs + i) *= -1;
    }
    return Stage::AccordingToPlan;
}
