//
//  CreateManagerment.cpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#include "CreateManagerment.hpp"

CreateManagement::CreateManagement(int num,int (&number)[],float distance):chance(number),num(num),distance(distance)
{
    //this->num = num;
    //this->distance = distance;
    //this->chance = chance;
}

int CreateManagement::randIndex()
{
    int randNum = rand() % 100 + 1;
    int tempNum = 1;
    for (int i = 0; i < num; i++) {
        if (randNum >= tempNum && randNum < tempNum + chance[i]) {
            return i;
        }
        else
            tempNum += chance[i];
    }
}