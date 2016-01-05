//
//  Track.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef Track_hpp
#define Track_hpp

#include <stdio.h>
#include "game.h"
#include <string.h>

class Track
{
    //int change_course_chance[3];
    int * change_course_chance;
    
public:
    //cocos2d::Sprite * bg;
    //CC_SYNTHESIZE(std::string, bgfilename, BgFileName);
    
    CC_SYNTHESIZE(TrackState, trackState, TrackState);
    CC_SYNTHESIZE(float, courseSpeed, CourseSpeed);
    CC_SYNTHESIZE(int, colNum, ColNum);
    CC_SYNTHESIZE(float, circuitWidth, CircuitWidth);
    CC_SYNTHESIZE(float, changeCourseDistance, ChangeCourseDistance);
//  CC_SYNTHESIZE(float,tempdistance, TempDistance);
    
//    friend class CreateManagement;
    
public:
    void setChangeChance(int * num);
//    int getChangeChance();
    
    //bool isNeedChangeChannel();
    TrackState changeChannel();
    Track(void);
    virtual ~Track(void);
    
};

#endif /* Track_hpp */
