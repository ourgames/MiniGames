//
//  Track.cpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/28.
//
//

#include "Track.hpp"

Track::Track()
{
    int chancenum[3] = {30,30,40};
    //int * chancenum = {30,30,40};
    //读取配置文件
    
    setTrackState(Middle);
    setCircuitWidth(80);
    setColNum(7);
    setCourseSpeed(50);
    setChangeCourseDistance(3000);
    setChangeChance(chancenum);
    setTempDistance(0);
}

void Track::setChangeChance(int *num)
{
    for (int i = 0; i <3 ; i++) {
        change_course_chance[i] = num[i];
    }
}

bool Track::isNeedChangeChannel()
{
    float td = getTempDistance();
    float temp = getChangeCourseDistance();
    if (td >= temp) {
        td -= temp;
        setTempDistance(td);
        return true;
    }
    return false;
}

void Track::changeChannel()
{
    if (isNeedChangeChannel()) {
        ;
    }
}