//
//  total.hpp
//  MOT
//
//  Created by Hans on 4/30/16.
//  Copyright © 2016 Hans. All rights reserved.
//

#ifndef total_hpp
#define total_hpp

#include <iostream>
#include <cv.h>
#include <math.h>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <assert.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <algorithm>
#include "Vector2.hpp"
#include "Matrix.h"

#pragma comment(lib, "mclmcrrt.lib")
#pragma comment(lib, "mclmcr.lib")
#pragma comment(lib, "CFTracker.lib")

using namespace cv;
using namespace std;

/****************************Global Variable Declararion****************************/
//³õÊ¼»¯¶ÁÈëÊý¾ÝµÄ±ßÔµ
extern const CvPoint ROI_LeftTop;
extern const CvPoint ROI_RightDown;

//½øÐÐÊµ¼ÊMCMCËã·¨µÄ±ßÔµ
extern const CvPoint Border_LeftTop;
extern const CvPoint Border_RightDown;

//matlab data address
extern const char path[];

//relationship threshold
extern const double edge_threshold;

//the parameter for sigmoid function
extern const double width;
extern const double translation;

//all permutaion (don't change)
extern int** permutation_all;
extern int permutation_all_count;
extern int last_numtmp;

//all combination (dont change)
extern int** comination_all;
extern int comination_all_count;
extern int last_numtmp_comination;

//all hyph (dont change)
extern vector<vector<int> > hyp_all;
extern int hyp_all_count;
extern int last_numtmp_hyp;

//Variable used in print results, if detections in a tracklet is less than it, not print
extern int Delete_Less_Than;

//buffer of lost in frames
extern int GLOBAL_DELETE_BUFFER;

//boundary of the neighbourhood
extern int bound;
/**********************************End Variable************************************/
/**********************************************************************************/
/*****************************Sturcture Declaration********************************/
//Reading Data Structure
//class FILEPARAM{
//public:
//    std::vector<string> *PicArray;
//    std::vector<string> *TxtArray;
//};
//Detection Structure
class PointVar{
private:
    bool delet;
public:
    Vector2<double> position;	//t is the center of the detection(width)
    double trust; //Size is the width
    int width, height,frame,id;
    bool Use;
    double* apfeature;
    void print(){
        std::cout<<"Frame:"<<frame<<" ID:"<<id<<" x:"<<position.x<<" y:"<<position.y<<" width:"<<width<<" height:"<<height<<" confidence: "<<trust<<'\n';
    }
    void drawprint(){
        std::cout<<"Frame:"<<frame<<" x:"<<position.x-width/2<<" y:"<<position.y-width/2<<" width:"<<width<<" height:"<<height<<'\n';
    }
    PointVar(int frame1,double x1, double y1, double width1, double height1, double trust1, int ID1){
        cv::Point Border_lt = Border_LeftTop;
        cv::Point Border_rd = Border_RightDown;
        
        frame=frame1;
        id=ID1;
        int row = (int)(y1 + height1/2);
        int col =(int)( x1 + width1/2);
        position.x=col;
        position.y=row;
        width=(int)width1;
        height=(int)height1;
        trust=trust1;
        Use=false;
        delet=false;
        apfeature=NULL;
        //if(width < 10 || height < 10) delet=true;
        if (! ((int)x1 > Border_lt.x && (int)x1 < Border_rd.x && (int)y1 > Border_lt.y && (int)y1 < Border_rd.y))
            delet=true;
    }
    PointVar(){}
    bool delete_judge(){return delet;}
    ~PointVar(){
        delete []apfeature;
    }
};
//Tracklet Structure
class tracklet{
public:
    int delete_counting; //buffer detection frames
    int printbool;  // indicates whether to print in final results or not
    Vector2<double> velocity;
    std::vector <PointVar*> storage;
    std::vector<double> relation;
    double lambda1;
    double lambda2;
public:
    tracklet();
    tracklet(PointVar *target);
    //~tracklet();
};
//DetectionArray saving all detections
extern std::vector<std::vector<PointVar>> DetectionArray;
//Current tracklets
extern std::vector<tracklet> tracklet_pool;
//All Tracklets
extern std::vector<tracklet> all_tracklet;
//End Tracklets
/****************************End Declaration of Structure***************************/


#endif /* total_hpp */
