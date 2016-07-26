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
#include <iomanip>
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
#include <cmath>
#include "Vector2.hpp"
//#include "Matrix.h"

#pragma comment(lib, "mclmcrrt.lib")
#pragma comment(lib, "mclmcr.lib")
#pragma comment(lib, "CFTracker.lib")

using namespace cv;
using namespace std;

/**************************** Global Variable Declararion ****************************/
//boarders
extern const CvPoint ROI_LeftTop;
extern const CvPoint ROI_RightDown;
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

//max plan
extern double max_plan;
extern vector<int> best_plan;

//simiINDEX
extern double* simiIndex;
extern double* simiEdgeIndex;
//Variable used in print results, if detections in a tracklet is less than it, not print
extern int Delete_Less_Than;

//buffer of lost in frames
extern int GLOBAL_DELETE_BUFFER;

//boundary of the neighbourhood
extern int bound;

//+1 flag
extern int complete_flag;

//motion enable
extern int MOTION_ENABLE;

//tracklet id
extern int tracklet_id;
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
    int position_id;
    void print(){
        std::cout<<"Frame:"<<frame<<" ID:"<<id<<" x:"<<position.x<<" y:"<<position.y<<" width:"<<width<<" height:"<<height<<" confidence: "<<trust<<" Position_id: "<<position_id<<'\n';
    }
    void drawprint(){
        std::cout<<"Frame:"<<frame<<" x:"<<position.x-width/2<<" y:"<<position.y-height/2<<" width:"<<width<<" height:"<<height<<'\n';
    }
    double* output(){
        double* returnvalue = new double[4];
        returnvalue[0] = position.x-width/2;
        returnvalue[1] = position.y-height/2;
        returnvalue[2] = width;
        returnvalue[3] = height;
        return returnvalue;
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
        if ((! ((int)x1 > Border_lt.x && (int)x1 < Border_rd.x && (int)y1 > Border_lt.y && (int)y1 < Border_rd.y)))// || trust<0.9)
            delet=true;
    }
    PointVar(){}
    bool delete_judge(){return delet;}
    ~PointVar(){
        delete []apfeature;
    }
    
};
//Edgetype structure
class Edge_type_class{
public:
    int type;
    Vector2<double> pa;
    Edge_type_class(int t1){
        type = t1;
        pa.x = 0;
        pa.y = 0;
    }
    Edge_type_class(int t1, Vector2<double> p1){
        type = t1;
        pa = p1;
    }
    void print(){
        cout<<type<<"/"<<pa.x<<"/"<<pa.y<<"\t";
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
    std::vector<Edge_type_class> edgeType;
    std::vector<double> edgeWeights;
    double lambda1;
    double lambda2;
    int id;
public:
    //double current_app[1024];
    double area;
    double tracklet_weight;
    tracklet();
    tracklet(PointVar *target);
    //~tracklet();
};
class tmp_sort{
public:
    int index;
    int x;
    tmp_sort(int index1, int x1){
        index = index1;
        x = x1;
    }
    bool operator >(const tmp_sort& Pinfo) const{
        return x>Pinfo.x;
    }
    bool operator <(const tmp_sort& Pinfo) const{
        return x<Pinfo.x;
    }
};

//DetectionArray saving all detections
extern std::vector<std::vector<PointVar> > DetectionArray;
//Current tracklets
extern std::vector<tracklet> tracklet_pool;
//All Tracklets
extern std::vector<tracklet> all_tracklet;
//End Tracklets
/****************************End Declaration of Structure***************************/


#endif /* total_hpp */
