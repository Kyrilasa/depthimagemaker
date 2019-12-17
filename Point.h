#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point(double x,double y,double z,double camera_x,double camera_y,double camera_z);
        Point(double x,double y,double z);
        virtual ~Point();
        double x;
        double y;
        double z;
        double phi;
        double theta;
        double r;
};

#endif // POINT_H
