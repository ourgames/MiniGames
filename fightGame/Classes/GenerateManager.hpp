//
//  GenerateManager.hpp
//  fightGame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef GenerateManager_hpp
#define GenerateManager_hpp

typedef enum {
    track,
    block,
    item
} GenerateType;


#include <stdio.h>
class GenerateManager
{
    GenerateType type;
    float distance;
    int * chance;
    int number;//生成个数
    
};
#endif /* GenerateManager_hpp */
