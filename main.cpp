//
//  main.cpp
//  MOT
//
//  Created by Hans on 4/30/16.
//  Copyright © 2016 Hans. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cv.h>
#include "assistant.hpp"
using namespace std;
using namespace cv;
// ************ User name Predefine******* //
//#define USERNAME "Hans"
#define USERNAME "River"
// ************ Dataset Predefine *********** //
//#define Dataset "ADL-Rundle-1"
//#define Dataset "ADL-Rundle-3"
//#define Dataset "Town-Center"
//#define Dataset "KITTI-16"
//#define Dataset "ETH-Crossing"
//#define Dataset "ETH-Jelmoli"
//#define Dataset "ETH-Linthescher"
//#define Dataset "KITTI-19"
//#define Dataset "Venice-1"
//#define Dataset "PETS2009"
//#define Dataset "TUD-Crossing"
//#define Dataset "Canting5"
#define Dataset "canteenres"
// ***************** End **************** //

int main(){
    string UN = USERNAME;
    string DS = Dataset;
    string passp1 = "/Users/";
    string passp2 = "/Desktop/Xcode_MOT/2DMOT2015/test/";
    string passp3 = "/img1/";
    string passp4 = "/det/";
    string passp5 = "/Desktop/Xcode_MOT/Result_IMGs/";
    string passp6 = ".avi";
    string passp7 = "feature.txt";
    const std::string base_dir = passp1 + UN + passp2 + DS + passp3;
    const std::string data_dir = passp1 + UN + passp2 + DS + passp4;
    const std::string out_dir = passp1 + UN + passp5 + DS + passp6;
    const std::string result_img = passp1 + UN + passp5 + DS + "/";
    const std::string feature_dir = passp1 + UN +passp2 +DS + passp4 + passp7;
    int PicN = 1500;
    
    cout<<"Checking <base_dir>   : "<<base_dir<<endl;
    cout<<"Checking <data_dir>   : "<<data_dir<<endl;
    cout<<"Checking <feature_dir>: "<<feature_dir<<endl;
    //***************** Reading data into memory********************//
    cout<<"\n***************** Reading Data *****************\n\n";
    std::vector<string> PicArray;
    std::string Txtname, Listname,Imglist;
    Txtname = data_dir+"data.txt";
    Listname = data_dir+"list.txt";
    Imglist = base_dir + "img_list.txt";
    ifstream fin_data(Txtname);
    ifstream fin_list(Listname);
    ifstream fin_imglist(Imglist);      //preparing path and filename
    int totalframe;			//checking the total frames
    fin_imglist>>totalframe;
    if (PicN>totalframe) {
        cout<<"Warning in <main:PicN>: Exceeding Frame!\n";mypause();
        PicN = totalframe;
    }
    for(int i = 0; i < PicN; i++){
        int detection_num, nonsense;
        fin_list>>nonsense>>detection_num;
        string tmpstring;
        fin_imglist>>tmpstring;
        tmpstring = base_dir + tmpstring;
        PicArray.push_back(tmpstring);
        std::vector<PointVar> OneDetection;
        for (int j=0;j<=detection_num-1;j++){
            double x,y,width,height,trust;
            int frame;
            fin_data>>frame>>x>>y>>width>>height>>trust;		//detection data in
            PointVar tmp(frame,x,y,width,height,trust,j);		//construction
            if (!tmp.delete_judge()){       // delete some detections
                OneDetection.push_back(tmp);
            }
        }
        DetectionArray.push_back(OneDetection);
    }
    fin_data.close();
    fin_list.close();
    //ReadingExam(DetectionArray,PicArray);
    //mypause();
    ifstream feature(feature_dir);
    DetectionArray[6][0].print();
    mypause();
    for (int i=0; i <= DetectionArray.size() - 1 ;i++){
        for (int j = 0; j <= DetectionArray[i].size() - 1; j++){
            if (DetectionArray[i].size() == 0) break;
            double* feature_tmp;
            feature_tmp=new double[1024];
            int checkframe,checkid;
            feature>>checkframe>>checkid;
            
            //checking detection feature index
            if (checkframe != i+1 || checkid != DetectionArray[i][j].id){
                cout<<"<ERROR in main:reading feature> Detection feature index not matching!\n";
                cout<<"trueframe: "<<i+1<<"\tcheckframe: "<<checkframe<<endl;
                cout<<"trueid   : "<<DetectionArray[i][j].id<<"\tcheckid   : "<<checkid<<endl;
                mypause();
            }
            for (int i_tp = 0; i_tp <= 1023; i_tp ++){
                double writing_tmp;
                feature>>writing_tmp;
                //cout<<i_tp<<"\t"<<writing_tmp<<"\n";
                feature_tmp[i_tp]=writing_tmp;
            }
            DetectionArray[i][j].apfeature = feature_tmp;
        }
    }
    
    ReadingExam(DetectionArray,PicArray);
    cout<<"************ End Reading **************\n\n";
    
    int num_frame=(int)DetectionArray.size();
    vector<int> optimal_hype;
    double object_current;
    double max_object=0;
    int target_num=0;
    int tracklet_num=0;
    bool *target_link_flag;
    int difference;
    int bound=20;
    vector<int> plan;
    vector<int> one_to_one;
    for (int i = 0; i < num_frame; ++i)
    {
        if (i%100==0) {
            cout<<i<<endl;
        }
        difference=0;
        target_num=(int)DetectionArray[i].size();
        tracklet_num=(int)tracklet_pool.size();
        if (target_num==0) continue;
        max_object=-10000;
        target_link_flag=new bool[target_num];
        for (int p = 0; p < target_num; ++p)
        {
            target_link_flag[p]=0;
        }
        vector<vector<int> > candidate;
        candidate.assign(tracklet_num,vector<int>(0,0));
        for (int m=0; m<tracklet_num; m++) {
            PointVar *tmp=tracklet_pool[m].storage.back();
            for (int n=0; n<target_num; n++) {
                if ((abs(DetectionArray[i][n].position.x-tmp->position.x)<bound) &&
                        (abs(DetectionArray[i][n].position.y-tmp->position.y)<bound)) {
                    candidate[m].push_back(n);
                }
            }
        }
//        int tmp=candidate.size();
        plan.assign(tracklet_num,-1);
        one_to_one.assign(target_num,0);
        hyp_all.assign(0,vector<int>(tracklet_num,-1));
        generate_all_possibility2(candidate, 0, plan, one_to_one);
        
//        generate_all_possibility(target_num,tracklet_num);
        vector<int> plan(tracklet_num,-1);
        for (int j = 0; j < hyp_all.size(); ++j)
        {
//            if (i==72)
//                cout<<1<<endl;
            object_current=compute_gain(DetectionArray[i],hyp_all[j]);
            if (object_current>max_object)
            {
                max_object=object_current;
                
                optimal_hype=hyp_all[j];
            }
        }

        for (int k = 0; k < tracklet_num; ++k)
        {
            if (optimal_hype[k]!=-1){
                target_link_flag[optimal_hype[k]]=1;
                add_P2T(&tracklet_pool[k-difference],&DetectionArray[i][optimal_hype[k]]);
            }
            else{
                global_delete(k-difference);
                difference++;
            }
        }
        
        update_relation(tracklet_pool);
        
        for (int q = 0; q < target_num; ++q)
        {
            if (target_link_flag[q]==0)
            {
                tracklet tmp(&DetectionArray[i][q]);
                global_push(tmp);
            }
        }
        delete []target_link_flag;
    }
    
    int final_trackletpoolsize=(int) tracklet_pool.size();
    for (int i=0;i<final_trackletpoolsize;i++){
        all_tracklet.push_back(tracklet_pool[i]);
    }
    
    // ******************************* DRAW RECTANGLE ************************************* //
    
    std::vector<CvScalar> sVec;
    GetScalar(sVec);	//Get Color Vector
    VideoWriter writer(out_dir, CV_FOURCC('D', 'I', 'V', 'X'), 1, Size(1238,374));
    if (writer.isOpened()!=true){
        cout<<"ERROR in <main:VideoWriter>: initial failed!\n\n";
        mypause();
    }
    std::cout << "\n\n************************* START DRAWING ********************** \n\n" ;
    vector<vector<int>> trackletindex;
    vector<vector<int>> pointvarindex;
    trackletindex.resize(num_frame);
    pointvarindex.resize(num_frame);
    int num_tracklet=(int) all_tracklet.size();
    for (int i = 0;i <= num_tracklet-1;i++){
        if (num_tracklet==0) {cout<<"ERROR in <main>: Tracklet number=0!\n"; mypause(); break;}
        int tmp_num=(int)all_tracklet[i].storage.size();
        for (int j=0;j<=tmp_num-1;j++){
            if (tmp_num==0) {cout<<"Warning in <main>: Tracklet "<<j<<" has no pointvar in it!\n"; mypause();break;}
            //cout<<"tracklet_pool[i].storage[j]->frame: "<<tracklet_pool[i].storage[j]->frame<<'\n';
            trackletindex[all_tracklet[i].storage[j]->frame-1].push_back(i);
            pointvarindex[all_tracklet[i].storage[j]->frame-1].push_back(j);
        }
    }
    // ***Print all tracklet data as frame*** //
    cout<<"------ Print all tracklet data by frame ------\n\n";
    for (int i=0;i<=num_frame-1;i++){
        int tmp_num=(int) trackletindex[i].size();
        cout<<"Frame Number: "<<i+1<<"\n";
        if(tmp_num==0){
            cout<<"No data\n";
        }
        else {
            for (int j=0;j<=tmp_num-1;j++){
                cout<<"People ID: "<<trackletindex[i][j]<<" ";
                all_tracklet[trackletindex[i][j]].storage[pointvarindex[i][j]]->drawprint();
            }
        }
    }
    // ***END PRINT*** //
    std::cout<<"----------------------- Begin Draw --------------------------"<<std::endl;
    cout<<"Output direction check: "<<result_img<<endl;
//    mypause();
    for (int i = 0; i <PicN ; i++){
        //std::cout << "Image Dir:" << PicArray[i] << std::endl;
        Mat src = imread(PicArray[i]);		//read the i th picture
        
        std::stringstream ss;
        std::string FrameIndex;
        ss << i+1;
        ss >> FrameIndex;	// frame index
        
        putText(src, FrameIndex, Point(100, 100), CV_FONT_HERSHEY_COMPLEX, 2, Scalar(0, 0, 255));
        //cvPutText(src_new, Frameindex, CvPoint(100, 100), &font, CvScalar(0, 0, 255));	//draw frame number
        int framesize=(int)trackletindex[i].size();
        for (int j=0;j<=framesize-1;j++){
            int x,y,width,height,index;
            width=(int)all_tracklet[trackletindex[i][j]].storage[pointvarindex[i][j]]->width;
            height=(int)all_tracklet[trackletindex[i][j]].storage[pointvarindex[i][j]]->height;
            x=(int)(all_tracklet[trackletindex[i][j]].storage[pointvarindex[i][j]]->position.x-width/2);
            y=(int)(all_tracklet[trackletindex[i][j]].storage[pointvarindex[i][j]]->position.y-height/2);
            index=trackletindex[i][j];
            // x = (int)((double)x*1.875);
            // y = (int)((double)y*1.875);
            // width = (int)((double)width*1.875);
            // height = (int)((double)height*1.875);
            
            Rect r;
            r.x = x;
            r.y = y;
            r.width = width;
            r.height = height;
            
            Point t2;
            t2.x = x;
            t2.y = y;
            
            CvScalar s = sVec[index % sVec.size()];
            rectangle(src, r, s,3);
            
            std::stringstream ss;
            ss << index;
            std::string strIndex;
            ss >> strIndex;
            
            putText(src, strIndex, t2, CV_FONT_HERSHEY_COMPLEX, 1, s);		//draw index
        }
        //DrawDetectionDots(src, DetectionArray[i],4,Scalar(0,0,255),false);	//true代表是1080分辨率的
        
        //imshow("ff",src);
        //waitKey();
        
        // std::string outName;
        // outName = NumToString(std::string("Frame_"),i) + ".jpg";
        // outName = outDir + outName;
        // imwrite(outName,src);
        
        //namedWindow("a");
        //imshow("a",src);
        string out_dir_new, checkdir;
        //cvWaitKey(100);
        out_dir_new=result_img + NumToString2(i+1) + ".jpg";
//        checkdir = NumToString2(i+1) + ".jpg";
//        cout<<checkdir<<"  ";
//        if ((i+1)%7==0) cout<<endl;
        imwrite(out_dir_new,src);
        cvWaitKey(1);
      //  writer << src;
    }
    writer.release();
    std::cout<<"\n------------------------- END -------------------------------"<<std::endl;
    return 0;
}