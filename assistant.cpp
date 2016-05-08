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
void ReadingExam(std::vector<std::vector<PointVar>> &Array,vector<string> &img_list){
    //    for (int i = 0 ; i <= img_list.size() - 1 ; i ++){
    //        cout<<img_list[i]<<'\n';
    //    }
    for (int i = 0 ; i <= Array.size() - 1 ; i ++){
        for (int j=0; j <= Array[i].size() - 1 ; j++){
            if (Array[i].size()==0) break;
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
void Comotion_test(){
}
void A_test(int a, int b){
    std::cout<<A(a,b);
}
//**************END Test Functions**************//
double CoAppearance(tracklet *pre,PointVar *next){
    double totalsum=0;
    double sum1=0,sum2=0;
    int trackletsize=(int)pre->storage.size();
    double *preap, *nextap;
    preap=pre->storage[trackletsize-1]->apfeature;
    nextap=next->apfeature;
    for (int i=0 ; i < 1024 ; i ++){
        totalsum += preap[i] * nextap[i];
        sum1+=preap[i]*preap[i];
        sum2+=nextap[i]*nextap[i];
    }
    totalsum /=sqrt(sum1*sum2);
    return totalsum;
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
    double result,distance;
    Vector2<double> vector1,vector2,velocity;
    PointVar* tmp;
    int scale=0;
    velocity=track->velocity;
    scale=(int)track->storage.size();
    tmp=track->storage[scale-1];
    vector1=tmp->position;
    vector2=candidate->position;
    vector2=(vector2-vector1)/(candidate->frame-tmp->frame);
    
    if (velocity.absolute()==0 || vector2.absolute()==0)
        result=0;
    else
        result=velocity.dotProduct(velocity,vector2)/(velocity.absolute()*vector2.absolute());
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
    
    result=track->lambda1*simi_motion+track->lambda2*simi_app;
//    result=simi_app;
//    cout<<"\t\t"<<"simi_all: "<<result<<endl;
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
                
                //ÕâÀï¿ÉÒÔÔÙÉÌÈ¶
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
double compute_distance_variation(const PointVar *tracklet1_a,const PointVar *tracklet1_b,const PointVar *tracklet2_a,const PointVar *tracklet2_b){
    double difference;
    double distance1,distance2;
    Vector2<double> previous=tracklet1_a->position-tracklet1_b->position;
    Vector2<double> current=tracklet2_a->position-tracklet2_b->position;
    distance1=previous.absolute();
    distance2=current.absolute();
    difference=abs(distance2-distance1)/distance1;
    return difference;
}
void update_velocity(tracklet *track){
    int size=(int)track->storage.size();
    if (size <=1 ) return;
    //cout<<"track->storage[size-1]->frame:"<<track->storage[size-1]->frame<<'\n';
    //cout<<"track->storage[size-2]->frame:"<<track->storage[size-2]->frame<<'\n';
    track->velocity=(track->storage[size-1]->position-track->storage[size-2]->position)/(track->storage[size-1]->frame-track->storage[size-2]->frame);
    return;
}
void add_P2T(tracklet *track, PointVar *newdetection){
    track->storage.push_back(newdetection);
    update_velocity(track);
}
int cnt_tracklet(Matrix *hypothesis){
    int row=hypothesis->rows;
    int col=hypothesis->cols;
    int cnt=0;
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            if (hypothesis->ptr[i][j]==1){
                cnt++;
            }
        }
    }
    return cnt;
}
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
//n is the target number, m is the tracklet number
void generate_all_possibility(int n,int m){
    hyp_all_count=0;
    int num_tmp=0;
    if (last_numtmp_hyp != -1){
        for(int j = 0; j < last_numtmp_hyp; j ++)	delete []hyp_all[j];
        delete []hyp_all;
    }
    cout<<"Nodenum:"<<n<<"  trackletnum:"<<m<<"\n";
    if (n<m) {
        num_tmp=A(m,n);
        hyp_all=new int *[num_tmp];
        for (int i=0;i<=num_tmp-1;i++){
            hyp_all[i]=new int[m];
        }
        for (int i=0;i<=num_tmp-1;i++){
            for (int j = 0; j <= m - 1; j ++){
                hyp_all[i][j]=0;
            }
        }
        comb_main(m,n);
        Perm_main(n);
        //int t_time=-1;
        //if (factorial(n)!=0) t_time=A(m,n)/factorial(n)-1;
        for (int i=0;i<=A(m,n)/factorial(n)-1;i++){
            for (int j=0;j<=factorial(n)-1;j++){
                for (int k=0;k<=n-1;k++){
                    //cout<<comination_all[i][k]-1<<"   "<<permutation_all[j][k]<<"\n";
                    //system("pause");
                    hyp_all[hyp_all_count][comination_all[i][k]-1]=permutation_all[j][k];
                }
                hyp_all_count++;
            }
        }
        for (int i=0;i<=num_tmp-1;i++){
            for (int j = 0; j <= m - 1; j ++){
                hyp_all[i][j]--;
            }
        }
    }
    else if (n>=m){
        num_tmp=A(n,m);
        hyp_all=new int *[num_tmp];
        for (int i=0;i<=num_tmp-1;i++){
            hyp_all[i]=new int[m];
        }
        comb_main(n,m);
        Perm_main(m);
        int tmp_new;
        if (factorial(m)==0) tmp_new=0;
        else tmp_new=A(n,m)/factorial(m);
        for (int i=0;i<=tmp_new-1;i++){
            for (int j=0;j<=factorial(m)-1;j++){
                for (int k=0;k<=m-1;k++){
                    hyp_all[hyp_all_count][k]=comination_all[i][permutation_all[j][k]-1];
                }
                hyp_all_count++;
            }
        }
        for (int i=0;i<=num_tmp-1;i++){
            for (int j = 0; j <= m - 1; j ++){
                hyp_all[i][j]--;
            }
        }
    }
    //print and check
    
    
    int count_tmp=0;
    for (int i=0;i<=hyp_all_count-1;i++){
        for (int j=0;j<=m-1;j++){
//            cout<<hyp_all[i][j]<<" ";
        }
        count_tmp++;
//        cout<<"\n";
    }
//    cout<<num_tmp<<" "<<count_tmp<<"\n";
    
    last_numtmp_hyp=num_tmp;
}
double compute_gain(std::vector<PointVar> &detection,int *plan){
    double gain=0;
    int size=(int)tracklet_pool.size();
    double lambda;
    //compute the node gain
    for (int i = 0; i < size; ++i)
    {
        if (plan[i]!=-1){
            gain+=correlation_node(&tracklet_pool[i],&detection[plan[i]]);
//            PointVar* target1=tracklet_pool[i].storage.back();
//            PointVar* target2=&detection[plan[i]];
//            for (int j = 0; j < i; ++j)
//            {
//                if (plan[j]!=-1){
//                    PointVar* target3=tracklet_pool[j].storage.back();
//                    PointVar* target4=&detection[plan[j]];
//                    gain-=sigmoid(tracklet_pool[i].relation[j],translation,width)*compute_distance_variation(target1,target2,target3,target4);
//                }
//            }
        }
    }
    
    return gain;
}
void global_push(tracklet &tmp){
    tracklet_pool.push_back(tmp);
    for (int i = 0; i < tracklet_pool.size(); ++i)
    {
        //It is reasonable to assume there is no reltion between two targets without evidence
        tracklet_pool[i].relation.push_back(-100);
    }
}
void global_delete(int k){
    all_tracklet.push_back(tracklet_pool[k]);
    for (int i = 0; i < tracklet_pool.size(); ++i){
        if ((int)tracklet_pool.size()==0) break;
        vector<double>:: iterator iter=tracklet_pool[i].relation.begin();
        iter+=k;
        tracklet_pool[i].relation.erase(iter);
    }
    vector<tracklet>::iterator iter1=tracklet_pool.begin();
    iter1+=k;
    tracklet_pool.erase(iter1);
}
double sigmoid(double x,double a,double b){
    double denominator;
    denominator=1+exp((x-a)/b);
    return 1/denominator;
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
    sVec.push_back(CvScalar(128,128,255));
    sVec.push_back(CvScalar(255,128,255));
    sVec.push_back(CvScalar(255,255,0));
    sVec.push_back(CvScalar(128,0,255));
    sVec.push_back(CvScalar(0,255,255));
    sVec.push_back(CvScalar(255,255,0));
}
