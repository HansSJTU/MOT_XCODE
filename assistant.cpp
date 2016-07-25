//
//  assistant.cpp
//  MOT
//
//  Created by Hans on 4/30/16.
//  Copyright © 2016 Hans. All rights reserved.
//

#include "assistant.hpp"
void mypause(){
    cout<<"Enter to continue...\n";
    cin.get();
}
double GetDistance(Point t1,Point t2){
    double x1 = t1.x;
    double y1 = t1.y;
    
    double x2 = t2.x;
    double y2 = t2.y;
    
    double dx = (x1-x2)*(x1-x2);
    double dy = (y1-y2)*(y1-y2);
    
    double d = sqrt(dx+dy);
    
    return d;
}
string NumToString2(int i){
    std::string strPeopleNum;
    if(i < 10)
    {
        std::stringstream ss;
        ss << i;
        ss >> strPeopleNum;
        strPeopleNum = "00000" + strPeopleNum;
    }
    else if(i < 100)
    {
        std::stringstream ss;
        ss << i;
        ss >> strPeopleNum;
        strPeopleNum = "0000" + strPeopleNum;
    }
    else if(i < 1000)
    {
        std::stringstream ss;
        ss << i;
        ss >> strPeopleNum;
        strPeopleNum = "000" + strPeopleNum;
    }
    else
    {
        std::stringstream ss;
        ss << i;
        ss >> strPeopleNum;
        strPeopleNum = "00" + strPeopleNum;
    }
    
    return strPeopleNum;
}
//**************Testing Functions****************//
void ReadingExam(std::vector<std::vector<PointVar> > &Array,vector<string> &img_list){
    //    for (int i = 0 ; i <= (int)img_list.size() - 1 ; i ++){
    //        cout<<img_list[i]<<'\n';
    //    }
    for (int i = 0 ; i <= int(Array.size()) - 1 ; i ++){
        for (int j=0; j <= int(Array[i].size()) - 1 ; j++){
            if (int(Array[i].size())==0) break;
            Array[i][j].print();
        }
        cout<<'\n';
    }
}
void CoAppearance_test(){
    tracklet tracklet_tmp;
    //DetectionArray[1][0].print();
    //std::cin.get();
    tracklet_tmp.storage.push_back(&(DetectionArray[2][1]));
    //DetectionArray[0][0].print();
    double app_f1=CoAppearance(&tracklet_tmp,&DetectionArray[3][1]);
    //DetectionArray[1][0].print();
    cout << app_f1;
}
void A_test(int a, int b){
    std::cout<<A(a,b);
}
//**************END Test Functions**************//
double CoAppearance(tracklet *pre,PointVar *next){
    double totalsum=0;
    double sum1=0,sum2=0;
    double *preap, *nextap;
    int trackletsize=(int)pre->storage.size();
    preap = pre->storage[trackletsize-1]->apfeature;
//    if (trackletsize<=2)
//        preap = pre->storage[trackletsize-1]->apfeature;
//    else
//        preap = pre->current_app;
    nextap = next->apfeature;
    for (int i=0 ; i < 1024 ; i ++){
        totalsum += preap[i] * nextap[i];
        sum1+=preap[i]*preap[i];
        sum2+=nextap[i]*nextap[i];
        //totalsum += (preap[i] - nextap[i]) * (preap[i] - nextap[i]);
    }
    //totalsum /= 1024;
    totalsum /= sqrt(sum1*sum2);
    double angle_difference = acos(totalsum);
    double tmp_return = exp(-abs(angle_difference)*3);
//    if (pre->id == 26 && pre->storage[trackletsize-1]->frame == 2223){
//        pre->tracklet_weight = 2;
//    }
//    if (pre->id == 29 && pre->storage[trackletsize-1]->frame == 2223){
//        pre->tracklet_weight = 2;
//    }
    tmp_return *= pre->tracklet_weight;
    //totalsum = 4*totalsum - 2.6;
    //totalsum *= pre->tracklet_weight;
    //cout<<"cos: "<<totalsum<<' '<<"app: "<<tmp_return<<endl;
//    if (tmp_return < 0.1) {
//        return (10 * tmp_return - 1);
//    }
    return tmp_return;
}
//double CalcNodeAppearance(const Rect *preR,int FrameNum1,const Rect *nextR,int FrameNum2){
//    if(!isRectInBorder(preR) || !isRectInBorder(nextR))	//if not inborder, than return
//        return 0;
//    std::cout<<"First frame     :"<<FrameNum1<<" "<<*preR<<"\n";
//    std::cout<<"Second frame    :"<<FrameNum2<<" "<<*nextR<<"\n";
//    std::cout<<"Starting Calculating Appearance...\n";
//    
//    //    mwArray Path(path);
//    //    mwArray r1(1,1,mxDOUBLE_CLASS);
//    //    mwArray c1(1,1,mxDOUBLE_CLASS);
//    //    mwArray h1(1,1,mxDOUBLE_CLASS);
//    //    mwArray w1(1,1,mxDOUBLE_CLASS);
//    //    mwArray frame1(1,1,mxDOUBLE_CLASS);
//    //
//    //    r1(1,1) = preR->y;
//    //    c1(1,1) = preR->x;
//    //    h1(1,1) = preR->height;
//    //    w1(1,1) = preR->width;
//    //    frame1(1,1) = FrameNum1;
//    //
//    //    mwArray r2(1,1,mxDOUBLE_CLASS);
//    //    mwArray c2(1,1,mxDOUBLE_CLASS);
//    //    mwArray h2(1,1,mxDOUBLE_CLASS);
//    //    mwArray w2(1,1,mxDOUBLE_CLASS);
//    //    mwArray frame2(1,1,mxDOUBLE_CLASS);
//    //
//    //    r2(1,1) = nextR->y;
//    //    c2(1,1) = nextR->x;
//    //    h2(1,1) = nextR->height;
//    //    w2(1,1) = nextR->width;
//    //    frame2(1,1) = FrameNum2;
//    //
//    //    mwArray rScore(1,1,mxDOUBLE_CLASS);
//    //
//    //    CalcSimiV2(1,rScore,Path,r1,c1,h1,w1,frame1,r2,c2,h2,w2,frame2);
//    double *score = new double;
//    //    rScore.GetData(score,1);
//    //
//    //    std::cout<<"Appearance Calculating Done\n"<<std::endl;
//    return *score;
//}
bool isRectInBorder(const Rect *r){
    int x1 = r->x;
    int y1 = r->y;
    Point t1(x1,y1);
    int x2 = x1 + r->width;
    int y2 = y1 + r->height;
    Point t2(x2,y2);
    
    if (InBorder(t1)==false) cout<<"left_top exceeding!"<<"\n";
    if (InBorder(t2)==false) cout<<"right_bottom exceeding!"<<"\n";
    //if border is in ROI return true
    if(InBorder(t1) && InBorder(t2)){
        cout<<"Border Checking Good!\n";
        return true;
    }
    else
        return false;
}
bool InBorder(Point t){
    int x = t.x;
    int y = t.y;
    
    if((x >= ROI_LeftTop.x && x <= ROI_RightDown.x) && ( y >= ROI_LeftTop.y && y <= ROI_RightDown.y))
        return true;
    else
        return false;
}
double correlation_motion(tracklet *track,PointVar *candidate){
    if ((int)track->storage.size()<4) return 0;
    double result;
    Vector2<double> vector1,vector2,velocity,velocity_dif;
    PointVar* tmp;
    int scale=0;
    velocity=track->velocity;
    scale=(int)track->storage.size();
    tmp=track->storage[scale-3];
    vector1=tmp->position;
    Vector2<double> p1 = track->storage[scale-4]->position;
    Vector2<double> p2 = track->storage[scale-2]->position;
    
    p1 = vector1 + (p1 - vector1)/(track->storage[scale-3]->frame - track->storage[scale-4]->frame);
    p2 = vector1 + (p2 - vector1)/(track->storage[scale-2]->frame - track->storage[scale-3]->frame);
    vector1 = (p1 + p2 + vector1)/3.0;
    vector2 = candidate->position;
    vector2 = (vector2-vector1)/(candidate->frame-tmp->frame);
    velocity_dif = vector2 - velocity;
    if (velocity.absolute()==0 || vector2.absolute()==0)
        result=0;
    else{
        double angle_dif = Vector2<double>::dotProduct(velocity,vector2)/(velocity.absolute()*vector2.absolute());
        if (angle_dif<0)
            result = angle_dif * double(velocity_dif.absolute());
        else
            result = angle_dif / double(velocity_dif.absolute());
       // result = (angle_dif+1)/2;
        //cout<<angle_dif<<endl;
    }
    return result;
}
double correlation_node(tracklet *track, PointVar *candidate){
    int size;
    PointVar* tmp;
    double simi_motion,result,simi_app;

    size=(int)track->storage.size();
    tmp=track->storage[size-1];
    
    simi_motion=correlation_motion(track,candidate);
    
    simi_app=CoAppearance(track,candidate);
    
    if (MOTION_ENABLE == 1){
        result=track->lambda1*simi_motion+track->lambda2*simi_app;
    }
    else if (MOTION_ENABLE ==0){
        result=simi_app;
    }

//    cout<<"\t\t"<<"simi_all: "<<result<<endl;
//    cout<<simi_motion<<"\t"<<simi_app<<"\n";
    return result;
}
void update_relation(std::vector<tracklet> &tracklet_pool){
    //need to check
    PointVar* target1;
    PointVar* target2;
    PointVar* target3;
    PointVar* target4;
    
    int num1,num2;
    
    double correlation=0;
    
    int scale=(int)tracklet_pool.size();
    for (int i = 0; i < scale; ++i){
        for (int j = 0; j < i; ++j){
            num1=(int)tracklet_pool[i].storage.size();
            num2=(int)tracklet_pool[j].storage.size();
            if (num1>=2 && num2>=2){
                target1=tracklet_pool[i].storage[num1-2];
                target2=tracklet_pool[i].storage[num1-1];
                target3=tracklet_pool[j].storage[num2-2];
                target4=tracklet_pool[j].storage[num2-1];
                correlation=compute_distance_variation(target1,target2,target3,target4);
                
                if (correlation>=edge_threshold){
                    tracklet_pool[i].relation[j]-=1;
                    tracklet_pool[j].relation[i]-=1;
                }
                else{
                    tracklet_pool[i].relation[j]+=1;
                    tracklet_pool[j].relation[i]+=1;
                }
            }
            else
                return;
        }
    }
    return;
}
void update_edgetype(std::vector<tracklet> &tracklet_pool,int frame){
    int scale=(int)tracklet_pool.size();
    int num1, num2, frame1, frame2;
    if (scale == 0) return;
    for (int i = 0; i <= scale - 1; i++){
        for (int j = 0; j <= i - 1; j++){
            num1=(int)tracklet_pool[i].storage.size();
            num2=(int)tracklet_pool[j].storage.size();
            Vector2<double> speed1, speed2, location1, location2;
            double width1, height1, width2, height2;
            speed1 = tracklet_pool[i].velocity;
            speed2 = tracklet_pool[j].velocity;
            frame1 = tracklet_pool[i].storage[num1-1]->frame;
            frame2 = tracklet_pool[j].storage[num2-1]->frame;
            location1 = tracklet_pool[i].storage[num1-1]->position;
            location2 = tracklet_pool[j].storage[num2-1]->position;
            width1 = tracklet_pool[i].storage[num1-1]->width;
            height1 = tracklet_pool[i].storage[num1-1]->height;
            width2 = tracklet_pool[j].storage[num2-1]->width;
            height2 = tracklet_pool[j].storage[num2-1]->height;
            if (tracklet_pool[i].velocity.absolute() == 0 || tracklet_pool[j].velocity.absolute() == 0){
                if (abs(location1.x - location2.x) < (width1 + width2)*1 && abs(location1.y - location2.y) <(width1+width2)*1){
                    tracklet_pool[i].edgeType[j].type = 1;
                    tracklet_pool[j].edgeType[i].type = 1;
                    continue;
                }
                tracklet_pool[i].edgeType[j].type = -1;
                tracklet_pool[j].edgeType[i].type = -1;
                continue;
            }
//            if (tracklet_pool[j].id == 79 && tracklet_pool[i].id == 81 && tracklet_pool[i].storage[num1-1]->frame == 1719){
//                cout<<tracklet_pool[j].storage[num2-1]->frame;
//            }
            if (num1 >= 2 && num1>=2){
                double speed_variation = Vector2<double>::dotProduct(speed1, speed2)/(speed2.absolute() * speed1.absolute());
                double speed_abs_va = abs(speed1.absolute() / speed2.absolute());
                Vector2<double> relative_velcity = speed1 - speed2;
                Vector2<double> relative_position = location2 - location1;
                double oreantation = Vector2<double>::dotProduct(relative_velcity, relative_position)/(relative_velcity.absolute() * relative_position.absolute());
                // -1 not connected, 1 group, 0 occlusion, 2 getting closer, 3 getting away
                if (abs(location1.x - location2.x) < (width1 + width2) * 1.5 && abs(location1.y - location2.y) <(width1+width2)*1.5 && speed_variation >= 0.75 && speed_abs_va <= 1.5 && speed_abs_va >= 0.67) {
                    tracklet_pool[i].edgeType[j].type = 1;
                    tracklet_pool[j].edgeType[i].type = 1;
                }
                else if(abs(location1.x - location2.x) < (width1 + width2)/2 && abs(location1.y - location2.y) <(width1+width2)/2 && tracklet_pool[i].edgeType[j].type == 2){
                    tracklet_pool[i].edgeType[j].type = 1;
                    tracklet_pool[j].edgeType[i].type = 1;
                }
                else if(abs(location1.x - location2.x) < (width1 + width2) * 3 && abs(location1.y - location2.y) <(width1 + width2) * 3 /*&& speed_variation <= -0.8*/ && oreantation >= 0.5 && tracklet_pool[i].edgeType[j].type != 3){
                    tracklet_pool[i].edgeType[j].type = 2;
                    tracklet_pool[j].edgeType[i].type = 2;
                    tracklet_pool[i].edgeType[j].pa = speed1 * (frame - frame1 + 1) - speed2 * (frame - frame2 + 1);
                    tracklet_pool[j].edgeType[i].pa = speed2 * (frame - frame2 + 1) - speed1 * (frame - frame1 + 1);
                }
                else if(abs(location1.x - location2.x) < (width1 + width2) * 3 && abs(location1.y - location2.y) <(width1 + width2) * 3 /*&& speed_variation <= -0.8*/ && oreantation <= -0.5){
                    tracklet_pool[i].edgeType[j].type = 3;
                    tracklet_pool[j].edgeType[i].type = 3;
                    tracklet_pool[i].edgeType[j].pa = speed1 * (frame - frame1 + 1) - speed2 * (frame - frame2 + 1);
                    tracklet_pool[j].edgeType[i].pa = speed2 * (frame - frame2 + 1) - speed1 * (frame - frame1 + 1);
                }
                else if(abs(location1.x - location2.x) >= (width1 + width2) * 2){
                    tracklet_pool[i].edgeType[j].type = -1;
                    tracklet_pool[j].edgeType[i].type = -1;
                }
            }
            else {
                tracklet_pool[i].edgeType[j].type = -1;
                tracklet_pool[j].edgeType[i].type = -1;
            }
        }
    }
    //if ()
}

void update_edge_node_weight(std::vector<tracklet> &tracklet_pool,std::vector<PointVar> &detection){
    int size=(int)tracklet_pool.size();
    PointVar* target_tmp, *target_tmp2, *target1_track2, *target2_track2;
    
    //compute the node gain
    for (int i = 0; i < size; ++i){
        if (best_plan[i] == -1){
            tracklet_pool[i].tracklet_weight /= 1.1;
            for (int j = 0; j < i; j ++ ) {
                if (tracklet_pool[i].edgeType[j].type != -1){
                    tracklet_pool[i].edgeWeights[j] /= 1.1;
                    tracklet_pool[j].edgeWeights[i] /= 1.1;
                }
            }
        }
        else if (best_plan[i]!= -1){
            target_tmp=tracklet_pool[i].storage.back();
            target_tmp2=&detection[best_plan[i]];
            
            //Node similarity calculation (using index to speed up)!
            double appearance_similaruty = simiIndex[i*(int(detection.size()))+best_plan[i]];
            //cout<<"appearance_similaruty: "<<appearance_similaruty<<endl;
            tracklet_pool[i].tracklet_weight = sigmoid(tracklet_pool[i].tracklet_weight - 1 + (appearance_similaruty - 0.2) * 5, 0, -1,2);
            //Edge similarity
            for (int j = 0 ; j < i; j ++) {
                if (tracklet_pool[i].edgeType[j].type != -1 && best_plan[j] != -1) {
                    int type = tracklet_pool[i].edgeType[j].type;
                    target1_track2=tracklet_pool[j].storage.back();
                    target2_track2=&detection[best_plan[j]];
                    double edge_similarity = compute_distance_variation_version2(target_tmp, target_tmp2, target1_track2,target2_track2, type);
                    //cout<<edge_similarity;
                    if (edge_similarity != -2){
                        tracklet_pool[i].edgeWeights[j] = sigmoid(tracklet_pool[i].edgeWeights[j] - 1 + (edge_similarity - 0.5) * 5, 0, -1,2);
                        tracklet_pool[j].edgeWeights[i] = tracklet_pool[i].edgeWeights[j];
                        //cout<<"edge_similarity: "<<edge_similarity<<endl;
                    }
                }
                else if (tracklet_pool[i].edgeType[j].type != -1 && best_plan[j] == -1) {
                    tracklet_pool[i].edgeWeights[j] /= 1.1;
                    tracklet_pool[j].edgeWeights[i] /= 1.1;
                }
            }
        }
    }
}
//1_a and 2_a belong to the previous frame, 1_b and 2_b belong to the present frame
//1_a will be linked to 2_a, 1_b will be linked to 2_b
double compute_distance_variation_version2(const PointVar *tracklet1_a,const PointVar *tracklet1_b,const PointVar *tracklet2_a,const PointVar *tracklet2_b, Edge_type_class Edge){
    double angle_difference, length_difference;
    double distance1,distance2;
    Vector2<double> previous = tracklet1_a->position - tracklet2_a->position;
    Vector2<double> current = tracklet1_b->position - tracklet2_b->position;
    Vector2<double> various = Edge.pa;
    if (Edge.type == 2 || Edge.type == 3){
        previous = previous + various;
    }
    angle_difference = Vector2<double>::dotProduct(previous,current)/(previous.absolute()*current.absolute());
    if (angle_difference>1){
        angle_difference = 0.9999;
    }
    double angle = acos(angle_difference);
    length_difference = current.absolute() - previous.absolute();
    //angle_difference = 1 / 2.0 * angle_difference + 1 / 2.0;
    //1 group, 0 occlusion, 2 getting closer, 3 getting away
    double tmp_gain;
    double denu = (tracklet1_a->width + tracklet2_a->width)/2;
    if (Edge.type == 1){
        tmp_gain = exp(-abs(length_difference)/(denu)) * exp(-abs(angle)*3);
    }
    else if (Edge.type == 0){
        tmp_gain = -2;
        return tmp_gain;
    }
    else if (Edge.type == 2){
        if (length_difference <= 0){
            //tmp_gain = exp(-abs(angle)*3);
            tmp_gain = exp(-abs(length_difference)/(denu)) * exp(-abs(angle)*3);
        }
        else
            tmp_gain = exp(-abs(length_difference)/(denu)) * exp(-abs(angle)*3);
    }
    else if (Edge.type == 3){
        if (length_difference >= 0)
            //tmp_gain = exp(-abs(angle)*3);
            tmp_gain = exp(-abs(length_difference)/(denu)) * exp(-abs(angle)*3);
        else
            tmp_gain = exp(-abs(length_difference)/(denu)) * exp(-abs(angle)*3);
    }
    
    if (tmp_gain < 0.1) {
        return -1;
    }
    //cout<<tmp_gain<<endl;
    return tmp_gain;
}
double compute_distance_variation(const PointVar *tracklet1_a,const PointVar *tracklet1_b,const PointVar *tracklet2_a,const PointVar *tracklet2_b){
//    if (tracklet1_a->frame!=tracklet2_a->frame || tracklet1_b->frame!=tracklet2_b->frame) {
//        return 0;
//    }
    
    double difference;
    double distance1,distance2;
    Vector2<double> previous=tracklet1_a->position-tracklet2_a->position;
    Vector2<double> current=tracklet1_b->position-tracklet2_b->position;
    difference = Vector2<double>::dotProduct(previous,current)/(previous.absolute()*current.absolute());
//    cout<<difference<<endl;
    return difference;
}
void update_velocity(tracklet *track){
    int size=(int)track->storage.size();
    if (size <= 6) return;
    if (size <= 6) {
        track->velocity = (track->storage[size-1]->position - track->storage[0]->position) / (track->storage[size-1]->frame - track->storage[0]->frame);
        return;
    }
    //cout<<"track->storage[size-1]->frame:"<<track->storage[size-1]->frame<<'\n';
    //cout<<"track->storage[size-2]->frame:"<<track->storage[size-2]->frame<<'\n';
    Vector2<double> position_queue[6];
    position_queue[0] = track->storage[size-1]->position;//1
    position_queue[1] = track->storage[size-2]->position;//2
    position_queue[2] = track->storage[size-3]->position;//3
    position_queue[3] = track->storage[size-4]->position;//4
    position_queue[4] = track->storage[size-5]->position;//5
    position_queue[5] = track->storage[size-6]->position;//6
    
    position_queue[0] = position_queue[1] + (position_queue[0] - position_queue[1])/(track->storage[size-1]->frame - track->storage[size-2]->frame);
    position_queue[2] = position_queue[1] + (position_queue[2] - position_queue[1])/(track->storage[size-2]->frame - track->storage[size-3]->frame);
    position_queue[3] = position_queue[4] + (position_queue[3] - position_queue[4])/(track->storage[size-3]->frame - track->storage[size-4]->frame);
    position_queue[5] = position_queue[4] + (position_queue[5] - position_queue[4])/(track->storage[size-4]->frame - track->storage[size-5]->frame);
    
    
    track->velocity=((position_queue[0]+position_queue[1]+position_queue[2])/3.0-(position_queue[3]+position_queue[4]+position_queue[5])/3.0)/(track->storage[size-2]->frame-track->storage[size-5]->frame);
    //cout<<track->velocity<<endl;
    return;
}
//void update_appearance(tracklet *track){
//    int size=(int)track->storage.size();
//    if (size <=2 ) return;
//    for (int i=0 ; i<=1023 ; i++){
//        track->current_app[i] = (track->storage[size-1]->apfeature[i]+track->storage[size-2]->apfeature[i]+track->storage[size-3]->apfeature[i])/3;
//    }
//}
void update_area(tracklet *track){
    int framenum = int(track->storage.size());
    if (framenum == 1)
        track->area = track->storage[0]->height * track->storage[0]->width;
    else{
        track->area = (track->area * (framenum-1) + track->storage[framenum-1]->width * track->storage[framenum-1]->height)/framenum;
    }
}
void add_P2T(tracklet *track, PointVar *newdetection){
    track->storage.push_back(newdetection);
    update_velocity(track);
   // update_area(track);
   // update_appearance(track);
}
//int cnt_tracklet(Matrix *hypothesis){
//    int row=hypothesis->rows;
//    int col=hypothesis->cols;
//    int cnt=0;
//    for (int i = 0; i < row; ++i){
//        for (int j = 0; j < col; ++j){
//            if (hypothesis->ptr[i][j]==1){
//                cnt++;
//            }
//        }
//    }
//    return cnt;
//}
//undone "generate_hyp"
//Matrix* generate_hyp(int trackletnum, int nodenum){
//    int hyp_num=A(nodenum,trackletnum);
//    if (hyp_num==-1) {
//        cout<<"Error: The number of nodenum is less than trackletnum!";
//        system("pause");
//    }
//}
int A(int a,int b){
    if (a<b) return -1;
    if (b==0) return 0;
    int tmp=1;
    for (int i = a; i>=a-b+1;i--){
        tmp=tmp*i;
    }
    return tmp;
}
void Swap(int& a, int& b){
    int c = a;
    a = b;
    b = c;
}
void Perm(int list[], int k, int m, int* count){
    if (k == m){
        for (int i = 0; i < m; ++ i){
            //cout << list[i];
            permutation_all[permutation_all_count][i]=list[i];
        }
        permutation_all_count++;
        ++(*count);
    }
    else{
        for (int i = k; i < m; ++i){
            Swap(list[k], list[i]);
            Perm(list, k + 1, m, count);
            Swap(list[i], list[k]);
        }
    }
}
int factorial(int m){
    int tmp=1;
    if (m==0) return 0;
    for (int i=1;i<=m;i++){
        tmp=tmp*i;
    }
    return tmp;
}
void Perm_main(int m){
    //initial, memory recycle
    permutation_all_count=0;
    if (last_numtmp != -1){
        for(int j = 0; j < last_numtmp; j ++)	delete []permutation_all[j];
        delete []permutation_all;
    }
    
    int count = 0;
    int num_tmp=factorial(m);
    permutation_all=new int *[num_tmp];
    for (int i=0;i<=num_tmp-1;i++){
        permutation_all[i]=new int[m];
    }
    int *list;
    list=new int[m];
    for (int i = 0; i < m; ++i){
        list[i] = i + 1;
    }
    Perm(list, 0, m, &count);
    /*print and check
     int count_tmp=0;
     for (int i=0;i<=permutation_all_count-1;i++){
     for (int j=0;j<=m-1;j++){
     cout<<permutation_all[i][j]<<" ";
     }
     count_tmp++;
     cout<<"\n";
     }
     cout<<num_tmp<<" "<<count_tmp<<"\n";*/
    last_numtmp=num_tmp;
    delete list;
}
void comb_main(int n,int m){
    //n>=m
    //initial, memory recycle
    comination_all_count=0;
    if (last_numtmp_comination != -1){
        for(int j = 0; j < last_numtmp_comination; j ++)	delete []comination_all[j];
        delete []comination_all;
    }
    int num_tmp;
    if (factorial(m)==0)
        num_tmp=0;
    else
        num_tmp=A(n,m)/factorial(m);
    comination_all=new int *[num_tmp];
    for (int i=0;i<=num_tmp-1;i++){
        comination_all[i]=new int[m];
    }
    int *list;
    list=new int[n];
    for (int i = 0; i < n; ++i){
        list[i] = i + 1;
    }
    Comb(0,n,m,list);
    /*
     //print and check
     int count_tmp=0;
     for (int i=0;i<=comination_all_count-1;i++){
     for (int j=0;j<=m-1;j++){
     cout<<comination_all[i][j]<<" ";
     }
     count_tmp++;
     cout<<"\n";
     }
     cout<<num_tmp<<" "<<count_tmp<<"\n";*/
    last_numtmp_comination=num_tmp;
    delete list;
}
void Comb(int step, int n, int m,int* list){
    int i;
    if((m == 0) || ((n - step) == m)) {
        for(i = step; i < n; i++)  list[i] = (m != 0);
        int tt_count=0;
        for(i = 0; i < n; i++){
            if (list[i]==1){
                comination_all[comination_all_count][tt_count]=i+1;
                tt_count++;
            }
        }
        comination_all_count++;
        return;
    }
    list[step] = 1, Comb(step + 1, n, m - 1, list);
    list[step] = 0, Comb(step + 1, n, m, list);
}
double compute_gain(std::vector<PointVar> &detection,vector<int> &plan,
                    vector<vector<int> > &candidate, int frame,double* simiIndex){
    double gain=0;
    int size=(int)tracklet_pool.size();
    double lambda;
    PointVar* target_tmp, *target_tmp2, *target1_track2, *target2_track2;
    PointVar* target1,*target2,*target3,*target4;
    
    //compute the node gain
    for (int i = 0; i < size; ++i)
    {
        if (plan[i]!=-1){
            target_tmp=tracklet_pool[i].storage.back();
            target_tmp2=&detection[plan[i]];
            double tmp1=target_tmp->position.x;
            double tmp2=target_tmp2->position.x;
            
            //Node similarity calculation (using index to speed up)!
            //gain+=correlation_node(&tracklet_pool[i],&detection[plan[i]]);
            double debug_gain = simiIndex[i*(int(detection.size()))+plan[i]];
            gain+=simiIndex[i*(int(detection.size()))+plan[i]];
            //cout<<"simiIndex: "<<debug_gain<<endl;
            
            /*
            double tmp_gain = 0;
            int tmp_counting = 0;
            //frame is the frame before wrong, target_tmp is the previous, target_tmp2 is the present
            if (frame == 951 && target_tmp->position_id == 1 && target_tmp2->position_id == 1){
                cout<<"1"<<endl;
            }
            //Edge similarity
            for (int j = 0 ; j < i; j ++) {
                if (tracklet_pool[i].edgeType[j].type != -1 && plan[j] != -1) {
                    Edge_type_class type = tracklet_pool[i].edgeType[j];
                    target1_track2=tracklet_pool[j].storage.back();
                    target2_track2=&detection[plan[j]];
                    
                    //i large, j small
                    if (tracklet_pool[i].id == 270 && tracklet_pool[j].id == 265 && target1_track2->frame == 951){// && target_tmp2->position_id == 3 && target2_track2->position_id == 4 ) {
                        cout<< target2_track2->frame;
                    }
                    
                    double tmp_return = compute_distance_variation_version2(target_tmp, target_tmp2, target1_track2,target2_track2, type);
                    //cout<< tmp_return<<endl;
                    if (tmp_return != -2) {
                        
                        // i large, j small
//                        if (tracklet_pool[i].id == 52 && tracklet_pool[j].id == 51 && target1_track2->frame == 2690) {
//                            tracklet_pool[i].edgeWeights[j] = 2;
//                        }
//                        if (tracklet_pool[i].id == 57 && tracklet_pool[j].id == 51 && target1_track2->frame == 2690){
//                            tracklet_pool[i].edgeWeights[j] = 2;
//                        }
//                        if (tracklet_pool[i].id == 56 && tracklet_pool[j].id == 51 && target1_track2->frame == 2690){
//                            tracklet_pool[i].edgeWeights[j] = 2;
//                        }
                        
                        
                        tmp_gain += tmp_return * tracklet_pool[i].edgeWeights[j];
                        //cout<<"tmp_return: "<<tmp_return<<endl;
                        tmp_counting ++;
                    }
                }
            }
            if (tmp_counting != 0){
               // cout << tmp_gain/tmp_counting << " " << tmp_gain << " " << tmp_counting << endl;
                tmp_counting = 1;
                gain += tmp_gain/tmp_counting;
            }
            */
            
//            if (frame>0) {
//                vector<int>::iterator iter;
//                bool flag;
//                for (int j=0; j<i; j++) {
//                    iter=find(candidate[i].begin(),candidate[i].end(),plan[j]);
//                    flag=iter==candidate[i].end()?false:true;
//                    if (flag) {
//                        target1_track2=tracklet_pool[j].storage.back();
//                        target2_track2=&detection[plan[j]];
//                        gain+=(compute_distance_variation(target_tmp, target_tmp2, target1_track2, target2_track2))/int(candidate.size());
//                        //cout<<compute_distance_variation(target_tmp, target_tmp2, target1_track2, target2_track2)<<endl;
//                    }
//                }
//            }

            //This is the correlation of the edge
            //            target1=tracklet_pool[i].storage.back();
            //            target2=&detection[plan[i]];
            //            for (int j = 0; j < i; ++j)
            //            {
            //                if (plan[j]!=-1){
            //                    PointVar* target3=tracklet_pool[j].storage.back();
            //                    PointVar* target4=&detection[plan[j]];
            //                    gain+=sigmoid(tracklet_pool[i].relation[j],translation,width)*compute_distance_variation(target1,target2,target3,target4);
            //                }
            //            }
        }
    }
    
    //cout<<gain<<endl;
    return gain;
}
void generate_best_plan(vector<vector<int> > &candidate,vector<int> &plan,vector<int> one_to_one,int trackletID){
    generate_all_possibility2(candidate, 0, plan, one_to_one, trackletID);
    
}
void generate_all_possibility2(vector<vector<int> > &candidate,
                               int pos, vector<int> &plan, vector<int> one_to_one, int trackletID)
{
    //bool flag=false;
    if (pos>=(int)candidate.size()) {
        double obj_current = compute_gain(DetectionArray[trackletID],plan, candidate,trackletID,simiIndex);
        if (obj_current > max_plan){
            best_plan = plan;
            max_plan = obj_current;
        }
        //hyp_all.push_back(plan);
        return;
    }
    if ((int)candidate[pos].size()==0) {
        plan[pos]=-1;
        generate_all_possibility2(candidate, pos+1,plan, one_to_one,trackletID);
    }
    else{
        for (int i=0; i<int(candidate[pos].size())+1; i++) {
            if (i == candidate[pos].size()) {
                if (complete_flag==1){
                    plan[pos]=-1;
                    generate_all_possibility2(candidate, pos+1,plan, one_to_one,trackletID);
                }
            }
            else {
                if (one_to_one[candidate[pos][i]]==0) {
                    plan[pos]=candidate[pos][i];
                    one_to_one[candidate[pos][i]]=1;
                    generate_all_possibility2(candidate, pos+1, plan, one_to_one,trackletID);
                    one_to_one[candidate[pos][i]]=0;
                }
                else {
                    plan[pos]=-1;
                    generate_all_possibility2(candidate, pos+1,plan, one_to_one,trackletID);
                }
            }
        }
    }
    
    return;
}

//n is the target number, m is the tracklet number
//void generate_all_possibility(int n,int m){
//    hyp_all_count=0;
//    int num_tmp=0;
//    if (last_numtmp_hyp != -1){
//        for(int j = 0; j < last_numtmp_hyp; j ++)	delete []hyp_all[j];
//        delete []hyp_all;
//    }
//    cout<<"Nodenum:"<<n<<"  trackletnum:"<<m<<"\n";
//    if (n<m) {
//        num_tmp=A(m,n);
//        hyp_all=new int *[num_tmp];
//        for (int i=0;i<=num_tmp-1;i++){
//            hyp_all[i]=new int[m];
//        }
//        for (int i=0;i<=num_tmp-1;i++){
//            for (int j = 0; j <= m - 1; j ++){
//                hyp_all[i][j]=0;
//            }
//        }
//        comb_main(m,n);
//        Perm_main(n);
//        //int t_time=-1;
//        //if (factorial(n)!=0) t_time=A(m,n)/factorial(n)-1;
//        for (int i=0;i<=A(m,n)/factorial(n)-1;i++){
//            for (int j=0;j<=factorial(n)-1;j++){
//                for (int k=0;k<=n-1;k++){
//                    //cout<<comination_all[i][k]-1<<"   "<<permutation_all[j][k]<<"\n";
//                    //system("pause");
//                    hyp_all[hyp_all_count][comination_all[i][k]-1]=permutation_all[j][k];
//                }
//                hyp_all_count++;
//            }
//        }
//        for (int i=0;i<=num_tmp-1;i++){
//            for (int j = 0; j <= m - 1; j ++){
//                hyp_all[i][j]--;
//            }
//        }
//    }
//    else if (n>=m){
//        num_tmp=A(n,m);
//        hyp_all=new int *[num_tmp];
//        for (int i=0;i<=num_tmp-1;i++){
//            hyp_all[i]=new int[m];
//        }
//        comb_main(n,m);
//        Perm_main(m);
//        int tmp_new;
//        if (factorial(m)==0) tmp_new=0;
//        else tmp_new=A(n,m)/factorial(m);
//        for (int i=0;i<=tmp_new-1;i++){
//            for (int j=0;j<=factorial(m)-1;j++){
//                for (int k=0;k<=m-1;k++){
//                    hyp_all[hyp_all_count][k]=comination_all[i][permutation_all[j][k]-1];
//                }
//                hyp_all_count++;
//            }
//        }
//        for (int i=0;i<=num_tmp-1;i++){
//            for (int j = 0; j <= m - 1; j ++){
//                hyp_all[i][j]--;
//            }
//        }
//    }
//    //print and check
//    
//    
//    int count_tmp=0;
//    for (int i=0;i<=hyp_all_count-1;i++){
//        for (int j=0;j<=m-1;j++){
////            cout<<hyp_all[i][j]<<" ";
//        }
//        count_tmp++;
////        cout<<"\n";
//    }
////    cout<<num_tmp<<" "<<count_tmp<<"\n";
//    
//    last_numtmp_hyp=num_tmp;
//}

void global_push(tracklet &tmp){
    for (int i = 0; i < (int)tracklet_pool.size(); ++i)
    {
        //It is reasonable to assume there is no reltion between two targets without evidence
        tracklet_pool[i].relation.push_back(0);
        Edge_type_class tmp(-1);
        tracklet_pool[i].edgeType.push_back(tmp);
        //cout<<tracklet_pool.size()<<"\t"<<tracklet_pool[i].edgeType.size()<<endl;
        tracklet_pool[i].edgeWeights.push_back(1);
    }
    tracklet_pool.push_back(tmp);
}
int global_delete(int k){
    if (++tracklet_pool[k].delete_counting > GLOBAL_DELETE_BUFFER ){
        all_tracklet.push_back(tracklet_pool[k]);
        for (int i = 0; i < (int)tracklet_pool.size(); ++i){
            if ((int)tracklet_pool.size()==0) break;
            vector<double>:: iterator iter=tracklet_pool[i].relation.begin();
            iter += k;
            tracklet_pool[i].relation.erase(iter);
            
            vector<Edge_type_class>:: iterator iter1=tracklet_pool[i].edgeType.begin();
            iter1 += k;
            tracklet_pool[i].edgeType.erase(iter1);
            
            vector<double>:: iterator iter2=tracklet_pool[i].edgeWeights.begin();
            iter2 += k;
            tracklet_pool[i].edgeWeights.erase(iter2);
        }
        vector<tracklet>::iterator iter3=tracklet_pool.begin();
        iter3+=k;
        tracklet_pool.erase(iter3);
        return 1;
    }
    else return 0;
}
double sigmoid(double x,double a,double b,double c){
    double denominator;
    denominator=1+exp((x-a)/b);
    return c/denominator;
}
void GetScalar(std::vector<CvScalar> &sVec){
    sVec.push_back(CvScalar(0,0,255));
    sVec.push_back(CvScalar(255,0,0));
    sVec.push_back(CvScalar(0,255,0));
    sVec.push_back(CvScalar(255,0,255));
    sVec.push_back(CvScalar(0,255,255));
    sVec.push_back(CvScalar(255,255,0));
    sVec.push_back(CvScalar(128,0,255));
    sVec.push_back(CvScalar(0,128,255));
    sVec.push_back(CvScalar(128,255,0));
    sVec.push_back(CvScalar(0,255,128));
    sVec.push_back(CvScalar(255,128,0));
    sVec.push_back(CvScalar(255,0,128));
    sVec.push_back(CvScalar(128,128,255));
    sVec.push_back(CvScalar(128,255,128));
    sVec.push_back(CvScalar(255,128,128));
}
