#MOT Challenge
This is for **Multiple Object Tracking**.

Author: *Hanxiao He*, *Junxian He*


##Contents
1. [Instances](##Instances)
2. [To Do List](##To Do List)
3. [Edition Log](##Edition Log)
4. [Daily Update](##Daily Update)

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
##Edition Log

1. Consider relation from Frame 340 to Frame 355 to tackle the problem in Frame 348 (exchange) successfully. 

##Daily Update

####2016.6.28
* Modify the motion similarity module, a problem still need to be addressed.
* Modify the appearance similarity module, but it does not work well.

####2016.6.29
* Add the plan with the person link to nobody, thus can address the module problem that prefer to link rather than start a new tracklet.