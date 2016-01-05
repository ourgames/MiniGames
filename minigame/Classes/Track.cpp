//
//  Track.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Track.hpp"

Track::Track()
{
    trackState = Middle;
    courseSpeed = 50;
    colNum = 7;
    circuitWidth = 80;
    changeCourseDistance = 3000;
    
    change_course_chance = new int[3];
    memset(change_course_chance, 0, 3);
    
    change_course_chance[0] = 30;
    change_course_chance[1] = 30;
    change_course_chance[2] = 40;
    //bgfilename = "yejing.jpg";
    //bg = cocos2d::Sprite::create("yejing.jpg");
    
}

void Track::setChangeChance(int *num)
{
    for (int i = 0; i < 3; i++) {
        change_course_chance[i] = num[i];
    }
}

TrackState Track::changeChannel()
{
    int randNum = rand() % 100 + 1;
    int tempNum = 1;
    for (int i = 0; i < 3; i++) {
        if (randNum >= tempNum && randNum < tempNum + change_course_chance[i]) {
            trackState = (TrackState)i;
            return (TrackState)i;
        }
        else
            tempNum += change_course_chance[i];
    }
}

Track::~Track()
{
    delete change_course_chance;
}