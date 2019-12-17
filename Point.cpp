#include "Point.h"
#include "math.h"
#include <iostream>
#define PI 3.14159265
using namespace std;
Point::Point(double x,double y,double z,double camera_x,double camera_y,double camera_z)
{
    this->x = x-camera_x;
    this->y = y-camera_y;
    this->z = z-camera_z;
    this->r = sqrt(pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
    this->theta = acos(this->z/r) * 180.0 / PI;
    this->phi = atan2(this->y, this->x) * 180.0 / PI;
}

Point::Point(double x,double y,double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->r = sqrt(x*x + y*y + z*z);
    this->theta = acos(z/r) * 180.0 / PI;;
    this->phi = atan2(y, x) * 180.0 / PI;;
}

Point::~Point()
{
    //dtor
}
