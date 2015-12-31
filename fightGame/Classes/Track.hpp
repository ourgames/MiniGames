//
//  Track.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/28.
//
//

#ifndef Track_hpp
#define Track_hpp

#include <stdio.h>
#include <CreateManagerment.hpp>

typedef  enum {
    Left = 0,
    Middle = 1,
    Right = 2
} TrackState;

//int change_course_chance[3] = [30,30,40];

class Track
{
    int change_course_chance[3];
public:
    CC_SYNTHESIZE(TrackState, trackState, TrackState);
    CC_SYNTHESIZE(float, courseSpeed, CourseSpeed);
    CC_SYNTHESIZE(int, colNum, ColNum);
    CC_SYNTHESIZE(float, circuitWidth, CircuitWidth);
    CC_SYNTHESIZE(float, changeCourseDistance, ChangeCourseDistance);
    CC_SYNTHESIZE(float,tempdistance, TempDistance);
    
    friend class CreateManagement;
    
public:
    void setChangeChance(int * num);
    int getChangeChance();
    
    bool isNeedChangeChannel();
    void changeChannel();
    Track(void);
    ~Track(void){};
    
};
#endif /* Track_hpp */
