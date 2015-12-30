//
//  CreateManagerment.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#ifndef CreateManagerment_hpp
#define CreateManagerment_hpp

#include <stdio.h>

class CreateManagement
{
    int num;
    int * chance;
    float distance;
public:
    //int randIndex(int num,int * chance,float distance);
    CreateManagement(int num,int * chance,float distance);
    int randIndex(void);
    ~CreateManagement();
};
#endif /* CreateManagerment_hpp */
