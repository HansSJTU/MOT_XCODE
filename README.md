#MOT Challenge
This is for **Multiple Object Tracking**.

Author: *Hanxiao He*, *Junxian He*

##Contents
1. [Instances](##Instances)
2. [To Do List](##To Do List)
3. [Edition Log](##Edition Log)
4. [Daily Update](##Daily Update)
5. [Variable Setting](##Variable Setting)

##Instances
* The Fifth Canteen
    * Frame 290 
    * ~~Frame 348 (exchange)~~ (see edition log1)
    * Frame 1016-1017 (exchange)
    * 1718-1719 (model issue! prefer to link rather than to start a new tracklet)
    * 1814-1816 (need to be solved by motion)
    * 2300 (wrong detection can lead to big issuses!)
    * 3423 (occlusion)
    * 4577 (exchange)
    * 4586 (wrong detection)
    * 4687-4688 (lacking detection caused exchange)

* The Tianmu Road
    * 832-833 exchange
    * 847 model issue
    * 1024 exchange
    * 1074-1076 detection loss error
    * 1085 same as the former
    * 1662 detection loss 
    * 1743-1746 model issues preferring linking 
    * 1890-2000 group wrong detection
    * 2214-2215 loss detection
    * 2232 exchange
    * 2458 loss detection caused exchange
    * 2524 wrong detection caused exchange
    * 2701 wrong detection caused exchange with wrong detection
    * 2770 exchange
    * 3993 model issue
    * 4103 wrong detection caused exchange with wrong detection
    * 4128 exchange caused by loss detection
    * 4164 exchange caused by loss detection
    * 4491 exchange caused by loss detection 
    * 4504 wide spread exchang caused by loss detection
    * 4512 exchange caused by loss detection 
    * 4965 exchange caused by loss detection
    * 4987 exchange caused by wrong detection

* KITTI-19
    * 168 exchange (detection lost)
        - 143 03 weight to 2 
    * 369 exchange  
        - 341 07 1.5
        - 171 04 2
    * 469 exchange caused by detection
        - 456 01 0.5
    * 476 exchange
    * 570 exchange
    * 698 exchange
    * 

##To Do List

1. Add the weight for appearance and motion


##Edition Log

1. Consider relation from Frame 340 to Frame 355 to tackle the problem in Frame 348 (exchange) successfully. 

##Daily Updates

####2016.6.28
* Modify the motion similarity module, a problem still need to be addressed.
* Modify the appearance similarity module, but it does not work well.

####2016.6.29
* Add the plan with the person link to nobody, thus can address the module problem that prefer to link rather than start a new tracklet.

####2016.6.30
* Fixed motion model issue mentioned in 2016.6.28
* Seminar
    * E-mail MOT author, asking for detection
    * Try to run Ouyang's detection on MOT dataset (Refinement, not complete algorithm)
    * Start valuating the weight for nodes and edges

####2016.7.8
* New feature and detection ready
* **First submission** to MOT testbench done (regard as baseline)

    |Rcll | Prcn | FAR| GT | MT | PT | ML | FP | FN | IDs | FM | MOTA | MOTP| 
    |-----|------|----|----|----|----|----|----|----|-----|----|------|-----|
    |66.2 |79.7  |1.79|721 |244 |335 |142 |10360| 20791| 1217| 1839|47.3|74.0|

* Performance enhancement: pre-calclate the affinity as an Index.
* Memory consumption optimization: avoid the plan list, memory usage can be limited within 100Mb.

* Lab Linux computer installed: change MODE to 1 to run on linux, use cMakeList to compile.

    ` cmake .`

    `make`

* Start evaluating

####2016.7.25
* **Second submission** to MOT benchmark

    |Rcll | Prcn |  FAR| GT | MT | PT  |ML|   FP  |  FN | IDs  | FM|  MOTA | MOTP |
    |-----|------|----|----|----|----|----|----|----|-----|----|------|-----|
    |65.3 | 81.0 | 1.62|721 |242| 335 |144| 9385| 21318 |1110| 1841|  48.2 | 74.0 |
    
* Seminor
    - Historical imformation. Consider tracklets as some feature as a graph.
    - Consider the transformation of the graph.
    - Learning methods
    - Forming confident tracklets, using these tracklets to apply graph matching.  


##Variable Setting
####Fisrt edition
1. KITTI-19/KITTI-16    1238X374
    * width*1
    * complete_flag==1
    * area (0.3,3.3)
    * GLOBAL_DELETE_BUFFER=5

2. ADL-Rundle-1/ADL-Rundle-3/AVG-TownCentre/    1920X1080
    * width*1.5 (caused by low fps)
    * complete_flag==0
    * area(0.3,3.3)
    * GLOBAL_DELETE_BUFFER=5

3. ETH-Jemoli/ETH-Crossing/ETH-Linthescher/    640X480
    * width*1
    * complete_flag==1
    * area(0.3,3.3)
    * GLOBAL_DELETE_BUFFER=5

4. Venice-1     1920X1080
    * width*1
    * complete_flag==1
    * area(0.3,3.3)
    * GLOBAL_DELETE_BUFFER=10

5. TUD-Crossing     640X480
    * **Enable motion**
    * complete_flag==1
    * GLOBAL_DELETE_BUFFER=5

6. PETS09-S2L2  768X576
    * **Enable motion**
    * complete_flag==0
    * GLOBAL_DELETE_BUFFER=5

####Second edition
1. All motion is not enable. 
2. Width and complete_flag are the same as the first edition.
3. The results of TUD-Crossing && ADL-Rundle-1 && ADL-Rundle-3 are the same as the First Edition.
4. Other dataset are involved with the similarity of edges.
5. Edge Type:
    * 0 (Occlusion):  abs(location1.x - location2.x) < (width1 + width2)/2 && abs(location1.y - location2.y) <(width1+width2)/2 && tracklet_pool[i].edgeType[j] == 2
    * 1 (Group): abs(location1.x - location2.x) < (width1 + width2) * 1.5 && abs(location1.y - location2.y) <(width1+width2)*1.5 && speed_variation >= 0.8 && speed_abs_va <= 1.5 && speed_abs_va >= 0.67
    * 2 (Closer): abs(location1.x - location2.x) < (width1 + width2) * 3 && abs(location1.y - location2.y) <(width1+width2) * 3 && oreantation >= 0.5 && tracklet_pool[i].edgeType[j] != 3
    * 3 (Away): abs(location1.x - location2.x) < (width1 + width2) * 3 && abs(location1.y - location2.y) <(width1+width2) * 3 /*&& speed_variation <= -0.8*/ && oreantation <= -0.5
    * -1 (Not involved): abs(location1.x - location2.x) >= (width1 + width2) * 2
2. Edge weight:
    * sigmoid(tracklet_pool[i].edgeWeights[j] - 1 + (edge_similarity - 0.5) * 5, 0, -1,2)
3. Vertex weight:
    * sigmoid(tracklet_pool[i].tracklet_weight - 1 + (appearance_similaruty - 0.2) * 5, 0, -1,2)
