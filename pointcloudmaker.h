#ifndef POINTCLOUDMAKER_H
#define POINTCLOUDMAKER_H

#include <fstream>
#include <vector>
#include <sstream>
#include "Point.h"
using namespace std;

class pointcloudmaker
{
    public:
        pointcloudmaker(string filename,int WIDTH,int HEIGHT);
        pointcloudmaker(string filename,int WIDTH,int HEIGHT,Point camera);
        virtual ~pointcloudmaker();
        void readPoints();
        void readPoints(Point camera);
        int dpWidth,dpHeight;
        string fileName;
        void writeOutPgm(string outputFilename,int pixelNeighbour);
        vector<Point> points2D;

        double drawYStep,drawXStep;
        double phiMin,phiMax;
        double thetaMin,thetaMax;
        double distanceGreyShadeStep;
};

#endif // POINTCLOUDMAKER_H
