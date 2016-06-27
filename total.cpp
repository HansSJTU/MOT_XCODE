//
//  total.cpp
//  MOT
//
//  Created by Hans on 4/30/16.
//  Copyright © 2016 Hans. All rights reserved.
//

#include "total.hpp"
/********TownCenter/ADL-1/ADL-3*************/
//const cv::Point ROI_LeftTop(30,30);
//const cv::Point ROI_RightDown(1000,540);
//
//const cv::Point Border_LeftTop(20,20);
//const cv::Point Border_RightDown(1020,556);
/********************************/

/********KITTI16/KITTI19*************/

//const CvPoint ROI_LeftTop(0,0);
//const CvPoint ROI_RightDown(1238,374);
//
//const CvPoint Border_LeftTop(0,0);
//const CvPoint Border_RightDown(1238,374);
/********************************/

/********Canteenres_5/Tianmu_Road*************/
const CvPoint ROI_LeftTop(0,0);
const CvPoint ROI_RightDown(640,480);

const CvPoint Border_LeftTop(0,0);
const CvPoint Border_RightDown(640,480);
/********************************/

/********Venice1*************/
//const cv::Point ROI_LeftTop(60,100);
//const cv::Point ROI_RightDown(970,540);
//
//const cv::Point Border_LeftTop(50,90);
//const cv::Point Border_RightDown(980,550);


/********************************/

/********Crossing/Linthescher/Jemoli/TUD-Crossing*************/
//const cv::Point ROI_LeftTop(20,20);
//const cv::Point ROI_RightDown(620,460);
//
//const cv::Point Border_LeftTop(10,10);
//const cv::Point Border_RightDown(630,470);
/********************************/

/********PETS2009*************/
//const cv::Point ROI_LeftTop(20,20);
//const cv::Point ROI_RightDown(740,540);
//
//const cv::Point Border_LeftTop(10,10);
//const cv::Point Border_RightDown(750,550);
/********************************/


/********Canting5*************/
//const cv::Point ROI_LeftTop(30,320);
//const cv::Point ROI_RightDown(1200,680);
//const CvPoint Border_LeftTop(0,0);
//const CvPoint Border_RightDown(640,480);
/********************************/

std::vector<std::vector<PointVar>> DetectionArray;

std::vector<tracklet> tracklet_pool;

std::vector<tracklet> all_tracklet;

tracklet::tracklet(){
    velocity=0;lambda1=0.5;lambda2=0.5;delete_counting=0;printbool=1;
    relation.resize(tracklet_pool.size()+1,0);
}

tracklet::tracklet(PointVar *target):velocity(0),lambda1(0.1),lambda2(0.9)
{
    storage.push_back(target);
    delete_counting=0;
    printbool=1;
    relation.resize(tracklet_pool.size()+1,0);
}

//const char path[] = "C:\\Users\\Hans\\Desktop\\MCMC_v4\\data\\KITTI-19\\img1\\";

const double edge_threshold=5;
const double width=1;
const double translation=0;


int** permutation_all=NULL;
int permutation_all_count=0;
int last_numtmp=-1;

int** comination_all=NULL;
int comination_all_count=0;
int last_numtmp_comination=-1;

vector<vector<int> > hyp_all;
int hyp_all_count=0;
int last_numtmp_hyp=-1;

int Delete_Less_Than=8;
int GLOBAL_DELETE_BUFFER=7;

