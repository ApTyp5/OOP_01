#include "primitives.h"
#include "processor.h"



Stage point_move(Point3D &point, const double *d)
{
    if (d == nullptr || (d + 1) == nullptr || (d + 2) == nullptr)
    {
        return Stage::NullptrReceived;
    }

    point.x += d[0];
    point.y += d[1];
    point.z += d[2];
    return Stage::AccordingToPlan;
}




Stage point_scale(Point3D &point, const double *d)
{
    if (d == nullptr)
    {
        return Stage::NullptrReceived;
    }

    point.x *= (*d);
    point.y *= (*d);
    point.z *= (*d);
    return Stage::AccordingToPlan;
}


Stage point_rotate(Point3D &point, const double *d)
{
    if (d == nullptr || (d + 1) == nullptr || (d + 2) == nullptr)
    {
        return Stage::NullptrReceived;
    }

    point_rotateOX(point, *d);
    point_rotateOY(point, *(d + 1));
    point_rotateOZ(point, *(d + 2));

    return Stage::AccordingToPlan;
}

Stage point_rotateOX(Point3D &point, const double &ang)
{
    if (fabs(ang) < 1e-5)
    {
        return Stage::ZeroAngleGiven;
    }

    double cosAng = cos(ang);
    double sinAng = sin(ang);

    double newY = point.y * cosAng + point.z * sinAng;
    double newZ = -point.y * sinAng + point.z * cosAng;

    point.y = newY;
    point.z = newZ;
    return Stage::AccordingToPlan;
}


Stage point_rotateOY(Point3D &point, const double &ang)
{
    if (fabs(ang) < 1e-5)
    {
        return Stage::ZeroAngleGiven;
    }

    double cosAng = cos(ang);
    double sinAng = sin(ang);

    double newX = point.x * cosAng - point.z * sinAng;
    double newZ = point.x * sinAng + point.z * cosAng;

    point.x = newX;
    point.z = newZ;
    return Stage::AccordingToPlan;
}

Stage point_rotateOZ(Point3D &point, const double &ang)
{
    if (fabs(ang) < 1e-5)
    {
        return Stage::ZeroAngleGiven;
    }

    double cosAng = cos(ang);
    double sinAng = sin(ang);

    double newX = point.x * cosAng + point.z * sinAng;
    double newY = -point.x * sinAng + point.z * cosAng;

    point.x = newX;
    point.y = newY;
    return Stage::AccordingToPlan;
}
