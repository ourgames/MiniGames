//
//  Player.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/25.
//
//

#include "Player.hpp"

Player * Player::create()
{
    Player * player = new (std::nothrow) Player();
    if (player && player->init()) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

Player::Player()
{
    
}

bool Player::init()
{
    cocos2d::Vec2 position;
    cocos2d::Size collisionSize;
    cocos2d::Vec2 speed;
    float score;
    float stamina;
    float staminaReduce;
    std::string filename;
    
    bool result;
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    std::string id = CommonUtil::itos(PLAYERID);
    
    //碰撞盒信息
    std::string collision = CommonUtil::getPropById(id, "collision");
    CCArray * colli = CommonUtil::split(collision.c_str(), ",");
    collisionSize.width = (dynamic_cast<CCString*>(colli->getObjectAtIndex(0)))->floatValue();
    collisionSize.height = (dynamic_cast<CCString*>(colli->getObjectAtIndex(1)))->floatValue();
    //速度信息
    std::string speedstr = CommonUtil::getPropById(id, "speed");
    speedstr.erase(0,1);
    speedstr.erase(speedstr.end()-1, speedstr.end());
    CCArray * speedli = CommonUtil::split(speedstr.c_str(), ",");
    speed.x = (dynamic_cast<CCString*>(speedli->getObjectAtIndex(0)))->floatValue();
    speed.y = (dynamic_cast<CCString*>(speedli->getObjectAtIndex(1)))->floatValue();
    //分数
    score = atof(CommonUtil::getPropById(id, "score").c_str());
    //体力值
    stamina = atof(CommonUtil::getPropById(id, "stamina").c_str());
    //
    staminaReduce = atof(CommonUtil::getPropById(id, "staminaReduce").c_str());
    //图片文件名
    filename = CommonUtil::getPropById(id, "filename");
  
    position.x = origin.x + visibleSize.width/2;
    position.y = origin.y + visibleSize.height/2;
    
    if (BaseDisplayObject::init(position, collisionSize, speed)) {
        
        SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
        frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
        actor = Sprite::createWithSpriteFrameName(filename);
        //actor = Sprite::create(filename);
        this->addChild(actor,1);
        
        mScore = score;
        mStamina = stamina;
        mStanimaReduce = staminaReduce;
        
        result = true;
    }
    else
        result = false;
    
    return result;
}

Player::~Player()
{
    
}

void Player::update(float dt)
{
    
}

void Player::onCollision(IDisplayObject *pCollisionTarget)
{
    
}