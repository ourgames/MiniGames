//
//  GameSprite.cpp
//  game
//
//  Created by 葛富臻 on 15/12/11.
//
//

#include "GameSprite.hpp"

USING_NS_CC;

GameSprite::GameSprite(void):_vector(ccp(0,0)),_screenSize(CCDirector::sharedDirector()->getWinSize())
{
}
GameSprite::~GameSprite(void){}