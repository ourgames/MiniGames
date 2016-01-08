//
//  Player.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "Player.hpp"

//Player::Player()
//{
//    total_stamina = 0;
//    stamina_reduce = 0;
//    score = 0;
//    pickUpDistance = 0;
//}

Player::~Player()
{
    
}

bool Player::init()
{
    if (Entity::init()) {
        setTotalStamina(600);
        setStaminaReduce(6);
        setScore(0);
        setPickUpDistance(60);
        setIsAlive(true);
        return true;
    }
    return false;
}