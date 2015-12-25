//
//  ItemRes.cpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/25.
//
//

#include "ItemRes.hpp"

ItemRes::ItemRes(void):speed(2.5f),w_index(0),h_index(0),m_isAtive(true)
{
    
}
ItemRes::~ItemRes(void)
{
    
}

// ItemRes * ItemRes::create(void)
//{
//    
//}
 void ItemRes::update(float dt)
{
    
}
 bool ItemRes::init()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
}
bool ItemRes::isCollasion()
{
    
}
bool ItemRes::isNear()
{
    
}
//void ItemRes::isCollasionCallback(cocos2d::Ref* pSender)
//{
//    
//}
//void ItemRes::isNearCallback(cocos2d::Ref* pSender)
//{
//    
//}
void ItemRes::show()
{
    if (m_isAtive) {
        this->setVisible(true);
    }
}
void ItemRes::hide()
{
    if (!m_isAtive) {
        this->setVisible(false);
    }
}
bool ItemRes::isAlive()
{
    return m_isAtive;
}