#include "pointcloudmaker.h"
#include "iostream"
#include "algorithm"
#include <math.h>

void printProgBar( int percent ){
  std::string bar;

  for(int i = 0; i < 50; i++){
    if( i < (percent/2)){
      bar.replace(i,1,"=");
    }else if( i == (percent/2)){
      bar.replace(i,1,">");
    }else{
      bar.replace(i,1," ");
    }
  }

  std::cout<< "\r" "[" << bar << "] ";
  std::cout.width( 3 );
  std::cout<< percent << "%     " << std::flush;
}


pointcloudmaker::pointcloudmaker(string filename,int WIDTH,int HEIGHT,Point camera)
{
    this->fileName = filename;
    this->dpHeight=HEIGHT;
    this->dpWidth=WIDTH;
    readPoints(camera);
}

pointcloudmaker::~pointcloudmaker()
{
    //dtor
}

void pointcloudmaker::readPoints(Point camera)
{
    ifstream fin;
    string line;
    double temp[3];
    double r_min=10000000,r_max=-1000000;
    double p_min=10000000,p_max=-1000000;
    double t_min=10000000,t_max=-1000000;
    fin.open(this->fileName);
    std::cout<<"Reading points from file..."<<std::endl;
    while (getline(fin, line))
    {

        stringstream in(line);
        int i = 0;
        while(in >> temp[i++]) {}
        if((temp[0]-camera.x)==0&&(temp[1]-camera.y)==0&&(temp[2]-camera.z)==0)
        {
            //if point that camera is on is in the pointcloud.xyz then skip.
        }else
        {
        Point tmp(temp[0],temp[1],temp[2],camera.x,camera.y,camera.z);
        this->points2D.push_back(tmp);
          if(tmp.r<r_min)
        {
            r_min=tmp.r;
        }
        if(tmp.r>r_max)
        {
            r_max=tmp.r;
        }
        if(tmp.phi<p_min)
        {
            p_min=tmp.phi;
        }
        if(tmp.phi>p_max)
        {
            p_max=tmp.phi;
        }
        if(tmp.theta<t_min)
        {
            t_min=tmp.theta;
        }
        if(tmp.theta>t_max)
        {
            t_max=tmp.theta;
        }
        }



        //phi is x theta is y
    }
    std::cout<<"[FINISHED]"<<std::endl;
    this->drawXStep = (double)this->dpWidth/(p_max-p_min);
    this->drawYStep = (double)this->dpHeight/(t_max-t_min);
    this->distanceGreyShadeStep = (r_max-r_min)/255;
    this->phiMin = p_min;
    this->phiMax = p_max;
    this->thetaMin = t_min;
    this->thetaMax = t_max;
    fin.close();
}
void pointcloudmaker::writeOutPgm(string outputFilename,int pixelNeighbourIn)
{
    ofstream img(outputFilename);
    img<<"P2"<<endl;
    img<<this->dpWidth<<" "<<this->dpHeight<<endl;
    img<<255<<endl;
    //setting all values to default 0
    int *imageRaster = new int[dpWidth*dpHeight];
    for(int i = 0; i<this->dpHeight; i++)
    {
        for(int j = 0; j<this->dpWidth; j++)
        {
            imageRaster[j*dpHeight+i]=0;
        }
    }
    //getting grayshade from pointcloud vector
    for(auto k : this->points2D)
    {
        int z = static_cast<int>(k.r/this->distanceGreyShadeStep);
        int greyShade = 255-z;
        if(k.phi<0)
        {
//            imageRaster[(int)(this->dpHeight-(this->thetaMax-k.theta)*this->drawYStep)][(int)(this->dpWidth-(this->dpWidth+k.phi*this->drawXStep))]=greyShade;
            imageRaster[(int)(this->dpWidth-(this->dpWidth+k.phi*this->drawXStep))*dpHeight+(int)(this->dpHeight-(this->thetaMax-k.theta)*this->drawYStep)]=greyShade;
        }
        else
        {
//            imageRaster[(int)(this->dpHeight-(this->thetaMax-k.theta)*this->drawYStep)][(int)(this->dpWidth-k.phi*this->drawXStep)]=greyShade;
            imageRaster[(int)(this->dpWidth-k.phi*this->drawXStep)*dpHeight+(int)(this->dpHeight-(this->thetaMax-k.theta)*this->drawYStep)]=greyShade;
            }
    }
    //writing out to file
    double sum = 0;
    double nn = 0;
//    double centerpos =(2*pixelNeighbourIn);
    std::cout<<"Writing out depth-image into "<<outputFilename<<std::endl;
    for(int i = 0; i<this->dpHeight; i++)
    {
        int _i = 100*((double)(i+1)/((double)this->dpHeight));
        printProgBar(_i);
        for(int j = 0; j<this->dpWidth; j++)
        {
            //if its black
            if(imageRaster[j*dpHeight+i]==0)
            {
                nn = 0;
                sum = 0;
                for(int k = (i-pixelNeighbourIn); k<(i+pixelNeighbourIn); k++)
                {
                    for(int l = (j-pixelNeighbourIn); l<(j+pixelNeighbourIn); l++)
                    {
                        if(k>=0&&k<this->dpHeight)
                        {
                            if(l>=0&&l<this->dpWidth)
                            {
//                                if(std::abs(imageRaster[l*dpHeight+k]-imageRaster[(l+1)*dpHeight+(k+1)])<30&&std::abs(imageRaster[l*dpHeight+k]-imageRaster[(l-1)*dpHeight+(k-1)])<30)
//                                {


                                    sum = sum + imageRaster[l*dpHeight+k];
                                    nn++;

//                                }
                            }
                        }

                    }
                }
                if(nn>0)
                {
                    sum/=nn;
                    imageRaster[j*dpHeight+i]=(int)sum;
                }
                img<<imageRaster[j*dpHeight+i]<<" ";

            }
            else
            {

                img<<imageRaster[j*dpHeight+i]<<" ";
                //first width and height
            }
        }
        img<<endl;
    }
    std::cout<<endl;
    img.close();
    //freeing memory
   delete []imageRaster;
}
