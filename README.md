# depthimagemaker
This small simple program have one input file with (x,y,z) coordinates within it and then it makes a .pgm image with the argument provided convolution pixel size.
There is also an option to specifiy the camera's position,
the sample pointcloud.xyz file is a lidar pointcloud from a crossroad.

```
  /*
        1. Parameterize the camera with x,y,z coordinates
        2. Initialize the helper class with the filename,WIDTH,HEIGHT,camera
        3. Call the helper class's writeOutPgm() function with parameters: output filename,convolution neighbour pixel number
    */
    Point camera(0,0,0);
    pointcloudmaker pc2dp("pointcloud.xyz",700,50,camera);
    pc2dp.writeOutPgm("output.pgm",2);
    
```
