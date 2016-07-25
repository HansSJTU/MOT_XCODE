//
//  total.cpp
//  MOT
//
//  Created by Hans on 4/30/16.
//  Copyright © 2016 Hans. All rights reserved.
//

#include "total.hpp"
/********TownCenter/ADL-1/ADL-3/Venice-1*************/
const CvPoint ROI_LeftTop(0,0);
const CvPoint ROI_RightDown(1920,1080);

const CvPoint Border_LeftTop(0,0);
const CvPoint Border_RightDown(1920,1080);
/********************************/

///********KITTI16/KITTI19*************/
//const CvPoint ROI_LeftTop(0,0);
//const CvPoint ROI_RightDown(1238,374);
//
//const CvPoint Border_LeftTop(0,0);
//const CvPoint Border_RightDown(1238,374);
/********************************/

/********Canteenres_5/Tianmu_Road/ETH-Jemoli/ETH-Crossing/ETH-Linthescher/TUD-Crossing*************/
//const CvPoint ROI_LeftTop(0,0);
//const CvPoint ROI_RightDown(640,480);
//
//const CvPoint Border_LeftTop(0,0);
//const CvPoint Border_RightDown(640,480);
/********************************/

/********PETS2009*************/
//const CvPoint ROI_LeftTop(0,0);
//const CvPoint ROI_RightDown(768,576);
//
//const CvPoint Border_LeftTop(0,0);
//const CvPoint Border_RightDown(768,576);
/********************************/


std::vector<std::vector<PointVar> > DetectionArray;

std::vector<tracklet> tracklet_pool;

std::vector<tracklet> all_tracklet;

tracklet::tracklet(){
    velocity=0;lambda1=0.5;lambda2=0.5;delete_counting=0;printbool=1;tracklet_weight=1;
    relation.resize((int)(tracklet_pool.size())+1,0);
    Edge_type_class tmp(-1);
    edgeType.resize(int(tracklet_pool.size())+1,tmp);
    edgeWeights.resize(int(tracklet_pool.size())+1,1);
    id = tracklet_id ++;
    tracklet_weight = 1;
}

tracklet::tracklet(PointVar *target):velocity(0),lambda1(0.5),lambda2(0.5)
{
    storage.push_back(target);
    delete_counting=0;
    printbool=1;
    relation.resize(int(tracklet_pool.size())+1,0);
    Edge_type_class tmp(-1);
    edgeType.resize(int(tracklet_pool.size())+1,tmp);
    edgeWeights.resize(int(tracklet_pool.size())+1,1);
    area = double(target->height * target->width);
    tracklet_weight = 1;
    id = tracklet_id ++;
//    if (target->frame==341 && target->id==7){
//        tracklet_weight = 1.5;
//    }
//    if (target->frame==171 && target->id==4){
//        tracklet_weight = 2;
//    }
//    if (target->frame==143 && target->id==3){
//        tracklet_weight = 2;
//    }
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

double max_plan=-10000;
double* simiIndex = NULL;
double* simiEdgeIndex = NULL;
vector<int> best_plan;

int Delete_Less_Than=5;
int GLOBAL_DELETE_BUFFER=5;
int bound=30;
int complete_flag=0;
int MOTION_ENABLE=0;
int tracklet_id=1;