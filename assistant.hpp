//
//  assistant.hpp
//  MOT
//
//  Created by Hans on 4/30/16.
//  Copyright © 2016 Hans. All rights reserved.
//

#ifndef assistant_hpp
#define assistant_hpp


# include "total.hpp"

//Read Detection Data into DetectionArray
extern std::vector<std::vector<PointVar>> DetectionArray;
extern std::vector<tracklet> tracklet_pool;
//push back a tracklet globally(including tracklet pool,all_tracklet and the relation vector in each tracklet)
void global_push(tracklet &tmp);
//delete a tracklet near globally(not including the all_tracklet)
void global_delete(int k);
//sigmoid function
double sigmoid(double a,double b,double c);
//Compute the cost
double compute_gain(std::vector<PointVar> &detection,vector<int> &plan);
//Get distance
double GetDistance(Point t1,Point t2);
//exchange int to string(add 0) (not used)
std::string NumToString2(int i);
//calculate appearance corelation
double CoAppearance(tracklet *pre, PointVar *next);//top api
//double CalcNodeAppearance(const Rect *preR,int FrameNum1,const Rect *nextR,int FrameNum2);
//used function in CalcNodeAppearance
bool isRectInBorder(const Rect *r);
bool InBorder(Point t);
//calculate motion
double correlation_motion(tracklet *track,PointVar *candidate);
//calculate total
double correlation_node(tracklet *track, PointVar *candidate);
//update edge relation
void update_relation(std::vector<tracklet> &tracklet_pool);
//computer distance difference
double compute_distance_variation(const PointVar *tracklet1_a,const PointVar *tracklet1_b,const PointVar *tracklet2_a,const PointVar *tracklet2_b);
//updating velocity
void update_velocity(tracklet *track);
//adding a PointVar to a Tracklet
void add_P2T(tracklet *track, PointVar *newdetection);
//hypothesis number
int cnt_tracklet(Matrix *hypothesis);
//A function
int A(int a,int b);
//Swap function
void Swap(int& a, int& b);
//Permutation all
void Perm_main(int m); // top API
void Perm(int list[], int k, int m, int* count);
//factorial
int factorial(int m);
//Combination
void comb_main(int n,int m);//top api
void Comb(int step, int n, int m,int* list);
//Generate all A(n,m) possibility
void generate_all_possibility(int n,int m);
void generate_all_possibility2(const vector<vector<int> > &candidate,
                               int pos, vector<int> &plan, vector<int> one_to_one);
//rectangle color define
void GetScalar(std::vector<CvScalar> &sVec);

//*************Testing Functions****************//
//Test Reading
void ReadingExam(std::vector<std::vector<PointVar>> &Array,vector<string> &img_list);
//Test Coappearance
void CoAppearance_test();
//Test Comotion
void Comotion_test();
//Test A function
void A_test(int a,int b);
//Pause (replace system("pause") in VS)
void mypause();
//******************End*********************//
#endif /* assistant_hpp */
