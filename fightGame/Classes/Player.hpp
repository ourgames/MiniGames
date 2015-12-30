//
//  Player.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/30.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Entity.hpp"

class Player : public Entity
{
public:
    CC_SYNTHESIZE(float, total_stamina, TotalStamina);
    CC_SYNTHESIZE(float, stamina_reduce, StaminaReduce);
    CC_SYNTHESIZE(float, score, Score);
};

#endif /* Player_hpp */
