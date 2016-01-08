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
#include "Track.hpp"

class Player : public Entity
{

    CC_SYNTHESIZE(float, total_stamina, TotalStamina);
    CC_SYNTHESIZE(float, stamina_reduce, StaminaReduce);
    CC_SYNTHESIZE(float, score, Score);
    CC_SYNTHESIZE(float, pickUpDistance, PickUpDistance);
    CC_SYNTHESIZE(bool, isAlive, IsAlive);
    
public:
    //Player(void);
    virtual ~Player();
    
    CREATE_FUNC(Player);
    
    virtual bool init();
    
    //Player * createPlayer(Track *track);
    
    //bool addActor();
    //bool getIsAlive();
    //void setIsAlive(bool var);
};

#endif /* Player_hpp */
