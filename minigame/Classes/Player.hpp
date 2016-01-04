//
//  Player.hpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
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
    CC_SYNTHESIZE(float, pickUpDistance, PickUpDistance);
};

#endif /* Player_hpp */
