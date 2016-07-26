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
#include <sys/stat.h>
#include <sys/types.h>
#include "assistant.hpp"
#include <stdlib.h>
using namespace std;
using namespace cv;
// ***************** Mode **************** //
#define MODE 0  // 0 MAC, 1 LINUX
// ************ User name Predefine******* //
#define USERNAME "Hans"
//#define USERNAME "River"
// ************ Dataset Predefine *********** //
//#define Dataset "ADL-Rundle-1"
//#define Dataset "ADL-Rundle-3"
//#define Dataset "AVG-TownCentre"
//#define Dataset "KITTI-16"
//#define Dataset "KITTI-19"
//#define Dataset "ETH-Crossing"
//#define Dataset "ETH-Jelmoli"
//#define Dataset "ETH-Linthescher"
//#define Dataset "Venice-1"
//#define Dataset "PETS09-S2L2"
//#define Dataset "TUD-Crossing"
//#define Dataset "canteenres"
#define Dataset "tianmuluv5"
//#define Dataset "zhuangyuange02"
// ***************** End **************** //

int main(){
    string DS = Dataset;
    string passp3 = "/img1/";
    string passp4 = "/det/";
    string passp6 = ".avi";
    string passp7 = "feature.txt";
#if MODE == 0
    string UN = USERNAME;
    string passp1 = "/Users/";
    string passp2 = "/Desktop/Xcode_MOT/2DMOT2015/test/";
    string passp5 = "/Desktop/Xcode_MOT/Result_IMGs/";
    string passp8 = "/Desktop/Xcode_MOT/Upload/";
    const std::string base_dir = passp1 + UN + passp2 + DS + passp3;
    const std::string data_dir = passp1 + UN + passp2 + DS + passp4;
    const std::string out_dir = passp1 + UN + passp5 + DS + passp6;
    const std::string result_img = passp1 + UN + passp5 + DS + "/";
    const std::string feature_dir = passp1 + UN + passp2 +DS + passp4 + passp7;
    const std::string upload_dir = passp1 + UN + passp8;
#elif MODE == 1
    string passp1 = "/home/sam/Desktop/Xcode_MOT/2DMOT2015/test/";
    string passp5 = "/home/sam/Desktop/Xcode_MOT/Result_IMGs/";
    string passp8 = "/home/sam/Desktop/Xcode_MOT/Upload/";
    const string base_dir = passp1 + DS + passp3;
    const string data_dir = passp1 + DS + passp4;
    const string out_dir = passp5 + DS + passp6;
    const string result_img = passp5 + DS + "/";
    const string feature_dir = passp1 + DS + passp4 + passp7;
    const string upload_dir = passp8;
#endif
    int start = 1;
    int totalFrame = 5000;
    int PicN = start + totalFrame - 1;
    cout<<"Checking <base_dir>   : "<<base_dir<<endl;
    cout<<"Checking <data_dir>   : "<<data_dir<<endl;
    cout<<"Checking <feature_dir>: "<<feature_dir<<endl;
    //***************** Reading data into memory********************//
    cout<<"\n***************** Reading Data *****************\n";
    std::vector<string> PicArray;
    std::string Txtname, Listname,Imglist;
    Txtname = data_dir+"data.txt";
    Listname = data_dir+"list.txt";
    Imglist = base_dir + "img_list.txt";
    ifstream fin_data(Txtname.c_str());
    ifstream fin_list(Listname.c_str());
    ifstream fin_imglist(Imglist.c_str());      //preparing path and filename
    int totalframe;			//checking the total frames
    fin_imglist>>totalframe;
    if (PicN>totalframe) {
        cout<<"Warning in <main:PicN>: Exceeding Frame!\n";
        //mypause();
        cout<<"Total frame number has been set to: ";
        PicN = totalframe;
        cout<<PicN<<endl;
    }
    cout<<"\n*************************  Reading det\n";
    std::vector<int> deleteFrame;
    std::vector<int> deleteID;
    int star_count = 0; //to count print "*"
    for(int i = 0; i < PicN; i++){
        for (int star_count_tmp=0 ; star_count_tmp <(int) ((i+1)/double(PicN)*100/4-star_count) ;star_count_tmp++){
            cout<<"*";
        }
        star_count=(int) (i+1)/double(PicN)*100/4;
        int detection_num, nonsense;
        fin_list>>nonsense>>detection_num;
        string tmpstring;
        fin_imglist>>tmpstring;
        tmpstring = base_dir + tmpstring;
        PicArray.push_back(tmpstring);
        std::vector<PointVar> OneDetection;
        std::vector<tmp_sort> sorting_x;
        int tmp_index = 0;
        for (int j=0;j<=detection_num-1;j++){
            double x,y,width,height,trust;
            int frame;
            fin_data>>frame>>x>>y>>width>>height>>trust;		//detection data in
            PointVar tmp(frame,x,y,width,height,trust,j);		//construction
            if (!tmp.delete_judge()){       // delete some detections
                tmp_sort sort_v(tmp_index ++, int(x));
                OneDetection.push_back(tmp);
                sorting_x.push_back(sort_v);
            }
            else {
               // deleteFrame.push_back(frame);
               // deleteID.push_back(j);
            }
        }
        sort(sorting_x.begin(), sorting_x.end());
        for (int l = 0; l <= int(sorting_x.size()) - 1; l ++ ){
            OneDetection[sorting_x[l].index].position_id = l+1;
        }
        DetectionArray.push_back(OneDetection);
    }
    cout<<"  Finished\n";
    fin_data.close();
    fin_list.close();
   // ReadingExam(DetectionArray,PicArray);
   // mypause();
    cout<<"\n*************************  Reading features\n";
    star_count = 0;
    int delete_count = 0;
    ifstream feature(feature_dir.c_str());
    for (int i=0; i <= int(DetectionArray.size()) - 1 ;i++){
        for (int star_count_tmp=0 ; star_count_tmp <(int) ((i+1)/double(DetectionArray.size())*100/4-star_count) ;star_count_tmp++){
            cout<<"*";
        }
        star_count=(int) (i+1)/double(DetectionArray.size())*100/4;
        for (int j = 0; j <= int(DetectionArray[i].size()) - 1; j++){
            if (DetectionArray[i].size() == 0) break;
            double* feature_tmp;
            feature_tmp=new double[1024];
            int checkframe,checkid;
            feature>>checkframe>>checkid;
            if (deleteFrame.size() != 0 && checkframe == deleteFrame[delete_count] && checkid == deleteID[delete_count]) {
                j--;
                delete_count++;
                for (int i_tp = 0; i_tp <= 1023; i_tp ++){
                    double tmp_wr;
                    feature>>tmp_wr;
                }
                //cout<<checkframe<<"\t"<<checkid<<endl;
                continue;
            }
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
    
    //ReadingExam(DetectionArray,PicArray);
    cout<<"  Finished";
    cout<<"\n************ End Reading **************\n\n";
    
    int num_frame=(int)DetectionArray.size();
    vector<int> optimal_hype;
    double object_current;
    double max_object=0;
    int target_num=0;
    int tracklet_num=0;
    bool *target_link_flag;
    int difference;
    
    vector<int> plan;
    vector<int> one_to_one;
    for (int i = start-1; i < num_frame; ++i)
    {
        if (i%2==0) {
            //cout<<i<<endl;
        }
        difference=0;
        target_num=(int)DetectionArray[i].size();
        tracklet_num=(int)tracklet_pool.size();
        if (target_num==0) continue;
        max_object=-10000;
        max_plan=-10000;
        target_link_flag=new bool[target_num];
        for (int p = 0; p < target_num; ++p)
        {
            target_link_flag[p]=0;
        }
        vector<vector<int> > candidate;
        candidate.assign(tracklet_num,vector<int>(0,0));
        cout<<i+1<<endl;
        double all_can=1;
        for (int m=0; m<tracklet_num; m++) {
            PointVar *tmp=tracklet_pool[m].storage.back();
            int dele_count = tracklet_pool[m].delete_counting;
            
            for (int n=0; n<target_num; n++) {
                double area1 = double(DetectionArray[i][n].width*DetectionArray[i][n].height);
                double area2 = tmp->width * tmp->height;
                //cout<<area1<<"\t"<<area2<<endl;
                if (MOTION_ENABLE == 1 || MOTION_ENABLE == 0){
                    if ((abs(DetectionArray[i][n].position.x-tmp->position.x)<tmp->width*1) && (abs(DetectionArray[i][n].position.y-tmp->position.y)<tmp->width*1) && (area1/area2>0.3 && area1/area2<3.3))
                    {
                        candidate[m].push_back(n);
                    }
                }
                //This is for linking the people according to the speed
                else if (MOTION_ENABLE == 1) {
                    Vector2<double> Track_v = tracklet_pool[m].velocity;
                    if (Track_v.absolute() == 0) {
                        if ((abs(DetectionArray[i][n].position.x-tmp->position.x)<tmp->width*1+1*dele_count) &&
                                (abs(DetectionArray[i][n].position.y-tmp->position.y)<width*1+1*dele_count)) {
                            candidate[m].push_back(n);
                        }
                    }
                    else {
                        double bd1,bd2;
                        if (dele_count==0){
                            bd1 = 15 + 2 * abs(Track_v.x);
                            bd2 = 15 + 2 * abs(Track_v.y);
                        }
                        else {
                            bd1 = 15 + (abs(Track_v.x) + 2) * (dele_count + 2);
                            bd2 = 15 + (abs(Track_v.y) + 2) * (dele_count + 2);
                        }
                        if ((abs(DetectionArray[i][n].position.x-tmp->position.x) < bd1) &&
                            (abs(DetectionArray[i][n].position.y-tmp->position.y) < bd2)) {
                            candidate[m].push_back(n);
                        }
                    }
                }
            }
            if (complete_flag==1)
                all_can *= (candidate[m].size()+1);
            else if (complete_flag==0){
                if (candidate[m].size()!=0)
                    all_can *= (candidate[m].size());
            }
            cout<<candidate[m].size()<<" ";
        }
        cout<<endl;
        cout<<all_can<<" "<<tracklet_num<<" "<<target_num<<endl<<endl;
        plan.assign(tracklet_num,-1);
        one_to_one.assign(target_num,0);
        //hyp_all.assign(0,vector<int>(tracklet_num,-1));
        
        simiIndex = new double [target_num*tracklet_num];
        for (int t1 = 0; t1 <= tracklet_num - 1 ; t1 ++){
            for (int t2= 0; t2 <= target_num - 1; t2 ++){
                simiIndex [ t1 * target_num + t2] = correlation_node(&tracklet_pool[t1],&DetectionArray[i][t2]);
            }
        }
//        int posibility1, posibility2;
//        posibility1 = tracklet_num * (tracklet_num - 1) / 2;
//        posibility2 = target_num * (target_num -1) / 2;
//        simiEdgeIndex = new double [posibility1 * posibility2];
//        for (int t1 = 0; t1 <= posibility1 - 1; t1 ++){
//            for (int t2 = 0; t2 <= posibility2 -1; t2 ++){
//                
//            }
//        }
        generate_best_plan(candidate,plan,one_to_one,i);
//        generate_all_possibility2(candidate, 0, plan, one_to_one);
//        cout<<int(hyp_all.size())<<endl<<endl;
//        for (int t1=0;t1<=int(hyp_all.size())-1;t1++){
//            for (int t2=0;t2<=int(hyp_all[t1].size())-1;t2++)
//                cout<<hyp_all[t1][t2]<<"\t";
//            cout<<endl;
//        }
//        generate_all_possibility(target_num,tracklet_num);
        vector<int> plan(tracklet_num,-1);

//        for (int j = 0; j < int(hyp_all.size()); ++j)
//        {
//            object_current=compute_gain(DetectionArray[i],hyp_all[j], candidate, i,simiIndex);
//            if (object_current>max_object)
//            {
//                max_object=object_current;
//                
//                optimal_hype=hyp_all[j];
//            }
//        }
        optimal_hype = best_plan;
        
        update_edge_node_weight(tracklet_pool,DetectionArray[i]);
        
        delete [] simiIndex;
        for (int k = 0; k < tracklet_num; ++k)
        {
            if (optimal_hype[k]!=-1){
                target_link_flag[optimal_hype[k]]=1;
                add_P2T(&tracklet_pool[k-difference],&DetectionArray[i][optimal_hype[k]]);
                tracklet_pool[k-difference].delete_counting=0;
            }
            else{
                int tmp=global_delete(k-difference);
                if (tmp==1)
                    difference++;
            }
        }
        
//        update_relation(tracklet_pool);
        
        for (int q = 0; q < target_num; ++q)
        {
            if (target_link_flag[q]==0)
            {
                tracklet tmp(&DetectionArray[i][q]);
                global_push(tmp);
            }
        }
        delete []target_link_flag;
        
        update_edgetype(tracklet_pool,i+1);
        cout<<"Vertex Weights:\n";
        for (int l = 0; l <= int(tracklet_pool.size()) - 1; l ++) {
            cout << tracklet_pool[l].id << "\t\t " ;
        }
        cout<<endl;
        for (int l = 0; l <= int(tracklet_pool.size() - 1); l ++) {
            cout << setprecision(2) << std::fixed << tracklet_pool[l].tracklet_weight << "\t\t";
        }
        cout<<endl<<endl;
        
        cout<<"Edge Weights:\n";
        for (int m = 0; m <= int(tracklet_pool.size()) - 1; m ++){
            cout<<tracklet_pool[m].id<<"\t";
        }
        cout<<endl<<endl;
        for (int l = 0; l <= int(tracklet_pool.size()) - 1; l ++){
            for (int m = 0; m <= int(tracklet_pool[l].edgeType.size()) - 1; m++) {
                cout<<setprecision(2) << std::fixed <<tracklet_pool[l].edgeWeights[m]<<"\t";
            }
            int last = int(tracklet_pool[l].storage.size()) - 1;
            if (last >= 0)
                //cout<<"Frame: "<<tracklet_pool[l].storage[last]->frame<<"\t position: "<<tracklet_pool[l].storage[last]->position_id;
                cout<<"ID:  "<<tracklet_pool[l].id;
            cout<<endl<<endl;
        }
        cout<<endl;
        
        cout<<"Edge Types:\n";
        for (int m = 0; m <= int(tracklet_pool.size()) - 1; m ++){
            cout<<tracklet_pool[m].id<<"\t\t";
        }
        cout<<endl<<endl;
        for (int l = 0; l <= int(tracklet_pool.size()) - 1; l ++){
            for (int m = 0; m <= int(tracklet_pool[l].edgeType.size()) - 1; m++) {
                cout<<tracklet_pool[l].edgeType[m].type<<"/"<<tracklet_pool[l].edgeType[m].pa<<"\t";
            }
            int last = int(tracklet_pool[l].storage.size()) - 1;
            if (last >= 0)
                //cout<<"Frame: "<<tracklet_pool[l].storage[last]->frame<<"\t position: "<<tracklet_pool[l].storage[last]->position_id;
                cout<<"ID:  "<<tracklet_pool[l].id;
            cout<<endl<<endl;
        }
    }
    
    int final_trackletpoolsize=(int) tracklet_pool.size();
    for (int i=0;i<final_trackletpoolsize;i++){
        all_tracklet.push_back(tracklet_pool[i]);
    }
    
    // ******************************* DRAW RECTANGLE ************************************* //
    
    std::vector<CvScalar> sVec;
    GetScalar(sVec);	//Get Color Vector
//    VideoWriter writer(out_dir, CV_FOURCC('D', 'I', 'V', 'X'), 1, Size(1238,374));
//    if (writer.isOpened()!=true){
//        cout<<"ERROR in <main:VideoWriter>: initial failed!\n\n";
//        mypause();
//    }
    std::cout << "\n\n************************* START DRAWING ********************** \n\n" ;
    vector<vector<int> > trackletindex;
    vector<vector<int> > pointvarindex;
    trackletindex.resize(num_frame);
    pointvarindex.resize(num_frame);
    int num_tracklet=(int) all_tracklet.size();
    for (int i = 0;i <= num_tracklet-1;i++){
        if (num_tracklet==0) {cout<<"ERROR in <main>: Tracklet number=0!\n"; mypause(); break;}
        int tmp_num=(int)all_tracklet[i].storage.size();
        if (all_tracklet[i].storage.size() <= Delete_Less_Than) {
            all_tracklet[i].printbool=0;
        }
        else {
            for (int j=0;j<=tmp_num-2;j++){
                if (tmp_num==0) {cout<<"Warning in <main>: Tracklet "<<j<<" has no pointvar in it!\n"; mypause();break;}
                int frame1 = all_tracklet[i].storage[j]->frame;
                int frame2 = all_tracklet[i].storage[j+1]->frame;
                double width1 = all_tracklet[i].storage[j]->width;
                double height1 = all_tracklet[i].storage[j]->height;
                double x1 = all_tracklet[i].storage[j]->position.x - width1/2;
                double y1 = all_tracklet[i].storage[j]->position.y - height1/2;
                double width2 = all_tracklet[i].storage[j+1]->width;
                double height2 = all_tracklet[i].storage[j+1]->height;
                double x2 = all_tracklet[i].storage[j+1]->position.x - width2/2;
                double y2 = all_tracklet[i].storage[j+1]->position.y - height2/2;
                for (int q = 0; q < frame2-frame1-1; q++) {
                    PointVar* tmp1 = new PointVar(frame1+q+1,(x2-x1)/(frame2-frame1)*(q+1)+x1,(y2-y1)/(frame2-frame1)*(q+1)+y1,(width2-width1)/(frame2-frame1)*(q+1)+width1,(height2-height1)/(frame2-frame1)*(q+1)+height1,-1,-1);
                    all_tracklet[i].storage.insert(all_tracklet[i].storage.begin()+j+q,tmp1);
                }
                j = j + frame2 - frame1 - 1;
                tmp_num += frame2 - frame1 - 1;
            }
        }
    }
    
//    for (int i = 0;i <= num_tracklet-1;i++){
//        int tmp_num=(int)all_tracklet[i].storage.size();
//        if (all_tracklet[i].printbool==1){
//            for (int j = 5;j <= tmp_num ;j+=5){
//                if ()
//            }
//        }
//    }
    
    
    for (int i = 0;i <= num_tracklet-1;i++){
        if (num_tracklet==0) {cout<<"ERROR in <main>: Tracklet number=0!\n"; mypause(); break;}
        int tmp_num=(int)all_tracklet[i].storage.size();
        for (int j=0;j<=tmp_num-1;j++){
            if (tmp_num==0) {cout<<"Warning in <main>: Tracklet "<<j<<" has no pointvar in it!\n"; mypause();break;}
            //cout<<"tracklet_pool[i].storage[j]->frame: "<<tracklet_pool[i].storage[j]->frame<<'\n';
            if (all_tracklet[i].printbool==1){
                trackletindex[all_tracklet[i].storage[j]->frame-1].push_back(i);
                pointvarindex[all_tracklet[i].storage[j]->frame-1].push_back(j);
            }
        }
    }
    std::cout<<"----------------------- Begin Draw --------------------------"<<std::endl;
    cout<<"Upload direction check: "<<upload_dir<<endl;
    mkdir(upload_dir.c_str(),00777);
    string upname = ".txt";
    string uploadtxt = upload_dir + DS + upname;
    cout<<"Upload file check: "<<uploadtxt<<endl;
    ofstream fout(uploadtxt.c_str());
    for (int i=0;i<=num_frame-1;i++){
        int tmp_num=(int) trackletindex[i].size();
        if(tmp_num==0){
            continue;
        }
        else {
            for (int j=0;j<=tmp_num-1;j++){
                double* tmp_out;
                tmp_out = all_tracklet[trackletindex[i][j]].storage[pointvarindex[i][j]]->output();
                fout<<i+1<<","<<trackletindex[i][j]<<","<< tmp_out[0] <<","<<tmp_out[1]<<","<<tmp_out[2]<<","<<tmp_out[3]<<","<<"-1,-1,-1,-1"<<endl;
                delete [] tmp_out;
            }
        }
    }
    // ***Print all tracklet data as frame*** //
//    cout<<"------ Print all tracklet data by frame ------\n\n";
//    for (int i=0;i<=num_frame-1;i++){
//        int tmp_num=(int) trackletindex[i].size();
//        cout<<"Frame Number: "<<i+1<<"\n";
//        if(tmp_num==0){
//            cout<<"No data\n";
//        }
//        else {
//            for (int j=0;j<=tmp_num-1;j++){
//                cout<<"People ID: "<<trackletindex[i][j]<<" ";
//                all_tracklet[trackletindex[i][j]].storage[pointvarindex[i][j]]->drawprint();
//            }
//        }
//    }
    // ***END PRINT*** //
    cout<<"Output direction check: "<<result_img<<endl;
    mypause();
    cout<<"\n*************************  Output img\n";
    string rm_ins = "rm -r ";
    rm_ins = rm_ins + result_img;
    system(rm_ins.c_str());
    mkdir(result_img.c_str(),00777);
    star_count=0;
    for (int i = start-1; i <PicN ; i++){
        for (int star_count_tmp=0 ; star_count_tmp <(int) ((i+1)/double(PicN)*100/4-star_count) ;star_count_tmp++){
            cout<<"*";
        }
        star_count=(int) (i+1)/double(PicN)*100/4;
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
            //index = trackletindex[i][j];
            index = all_tracklet[trackletindex[i][j]].id;
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
            
            CvScalar s = sVec[index % int(sVec.size())];
            rectangle(src, r, s,1);
            
            std::stringstream ss;
            ss << index;
            std::string strIndex;
            ss >> strIndex;
            if (all_tracklet[trackletindex[i][j]].storage[pointvarindex[i][j]]->id==-1) {
                strIndex += '*';
            }
            
            putText(src, strIndex, t2, CV_FONT_HERSHEY_SIMPLEX, 0.8, s);		//draw index
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
    //writer.release();
    std::cout<<"\n------------------------- END -------------------------------"<<std::endl;
    return 0;
}