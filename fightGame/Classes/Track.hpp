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

typedef  enum {
    Left,
    Middle,
    Right
} TrackState;

//int change_course_chance[3] = [30,30,40];

class Track
{
    CC_SYNTHESIZE(TrackState, trackState, TrackState);
    CC_SYNTHESIZE(float, courseSpeed, CourseSpeed);
    CC_SYNTHESIZE(int, colNum, ColNum);
    CC_SYNTHESIZE(float, circuitWidth, CircuitWidth);
    CC_SYNTHESIZE(float, changeCourseDistance, ChangeCourseDistance);
    
    int change_course_chance[3];

public:
    bool isNeedChangeChannel();
    void changeChannel();
    
};
#endif /* Track_hpp */
