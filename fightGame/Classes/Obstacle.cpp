//
//  Obstacle.cpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/24.
//
//

#include "Obstacle.hpp"
//#define INIT_X CCDirector::sharedDirector()->getVisibleSize().width + 30
//#define INIT_Y CCDirector::sharedDirector()->getVisibleSize().height / 3
Obstacle::Obstacle(void)
{
    m_isAtive = false;
}


Obstacle::~Obstacle(void)
{
}
void Obstacle::show()
{
//    if ( this->get !=NULL)
//    {
//        setVisible(true);
//        m_isAtive = true;
//    }
}
void Obstacle::hide()
{
//    if (GetSprite()!=NULL)
//    {
//        setVisible(false);
//        setPosition(ccp(810,CCRANDOM_0_1()*500-10));
//        //reset();
//        m_isAtive = true;
//    }
}
void Obstacle::reset()
{
//    if (GetSprite()!=NULL)
//    {
//        setPosition(cocos2d::ccp( CCRANDOM_0_1()*800+10 ,  CCRANDOM_0_1()*500-10));
//        m_isAtive = true;
//    }
}
bool Obstacle::isAlive()
{
    return m_isAtive;
}
bool  Obstacle::init()
{
    return true;
    
}
/*
bool Obstacle::IsCollideWithPlayer(Player *player)
{
    CCRect rect = player->GetBoundingBox();
    CCPoint point = getPosition();
    return rect.containsPoint(point);
}
 */
