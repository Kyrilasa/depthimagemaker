#include <iostream>
#include "Point.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include "pointcloudmaker.h"
using namespace std;

int main(int argc, char *argv[])
{
    /*
        1. Parameterize the camera with x,y,z coordinates
        2. Initialize the helper class with the filename,WIDTH,HEIGHT,camera
        3. Call the helper class's writeOutPgm() function with parameters: output filename,convolution neighbour pixel number
    */
    Point camera(0,0,0);
    pointcloudmaker pc2dp("pointcloud.xyz",700,50,camera);
    pc2dp.writeOutPgm("output.pgm",2);


    return 0;
}
