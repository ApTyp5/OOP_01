#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdlib.h>

#include "enums.h"

struct Relation
{
    size_t pn1, pn2; // pn = PointNumber
};

struct Point3D
{
    double x, y, z;
};

struct Point2D
{
    double x, y;
};

struct Line3D
{
    Point3D p1, p2;
};

struct Line2D
{
    Point2D p1, p2;
};

Stage point_move(Point3D &point, const double *d);
Stage point_scale(Point3D &point, const double *d);
Stage point_rotate(Point3D &point, const double *d);
Stage point_rotateOX(Point3D &point, const double &ang);
Stage point_rotateOY(Point3D &point, const double &ang);
Stage point_rotateOZ(Point3D &point, const double &ang);




#endif // PRIMITIVES_H
