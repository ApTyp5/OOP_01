#pragma once
#include <stdio.h>
#include <math.h>


#include "enums.h"
#include "primitives.h"


struct procOutput
{
    size_t num;
    Line2D *proj;
};

struct action
{
    Action type;
    union args
    {
        double dArgs[3];
        char * strArgs;
    } args;
};


struct figure
{
    bool is_init = false;

    size_t relNum = 0;
    Relation *rels = nullptr;

    size_t pointNum = 0;
    Point3D *points = nullptr;
};

struct veiwer
{
    Point3D eye {25, 25, 0};
    double zp = 10;
};


// [1]
Stage proc_action(procOutput &out, const action &action);


// [2]
Stage proc_load(figure &figure, const union action::args &args);
Stage proc_save(figure &figure, const union action::args &action);

Stage proc_transform(figure &figure, const action &action);

Stage proc_move(figure &figure, const union action::args &action);
Stage proc_scale(figure &figure, const union action::args &action);
Stage proc_rotate(figure &figure, const union action::args &action);
Stage proc_make_projection(procOutput &out, const figure &figure, const veiwer&);

// [3]

Stage makeXProj(double &answer, const veiwer &veiwer, const Point3D &point);
Stage makeYProj(double &answer, const veiwer &veiwer, const Point3D &point);



Stage act_fig_center_init(union action::args &args, size_t pnum, Point3D *points);
Stage act_revert(union action::args &args);


