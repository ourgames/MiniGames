//
//  Effect.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#ifndef Effect_hpp
#define Effect_hpp

#include <stdio.h>

typedef enum {
    add,
    des,
    other
} EffectDir;

class Effect
{
public:
//    CC_SYNTHESIZE(float, HPEffect, HPEffect);
//    CC_SYNTHESIZE(float, ScoreEffect, ScoreEffect);
//    CC_SYNTHESIZE(float, EffectTime, EffectTime);
//    CC_SYNTHESIZE(float, EffectDistance, EffectDistance);
//    CC_SYNTHESIZE(float, EffectSpeed, EffectSpeed);
//    
    int id;
    EffectDir ed;
    float value;
    float effecttime;
};
#endif /* Effect_hpp */
