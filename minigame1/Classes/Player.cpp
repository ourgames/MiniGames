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
//    mScore = 0;
//    mStamina = 0;
    mStanimaReduce = 0;
}

bool Player::init()
{
    cocos2d::Vec2 position;
    cocos2d::Size collisionSize;
    cocos2d::Size magnetSize;
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
    
    std::string magnet = CommonUtil::getPropById(id, "magnetsize");
    CCArray * magli = CommonUtil::split(magnet.c_str(), ",");
    magnetSize.width = (dynamic_cast<CCString*>(magli->getObjectAtIndex(0)))->floatValue();
    magnetSize.height = (dynamic_cast<CCString*>(magli->getObjectAtIndex(1)))->floatValue();
    
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
    position.y = origin.y + visibleSize.height/5;
    
    if (BaseDisplayObject::init(position, collisionSize, speed)) {
        
        //SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
        //frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
        //actor = Sprite::createWithSpriteFrameName(filename);
        actor = Sprite::create(filename);
        this->addChild(actor,1);
        this->setScale(0.3);
        this->setAnchorPoint(ccp(0,0));
        IAttribute * pStaminaAttribute = Attribute::create(AttributeType::STAMINA, stamina);
        IAttribute * pScoreAttribute = Attribute::create(AttributeType::SOCRE, score);
        IAttribute * pMagnetXAttribute = Attribute::create(AttributeType::MAGNET_SIZE_X, magnetSize.width);
        IAttribute * pMagnetYAttribute = Attribute::create(AttributeType::MAGNET_SIZE_Y, magnetSize.height);
        
        if (pStaminaAttribute && pScoreAttribute && pMagnetXAttribute && pMagnetYAttribute ) {
            addAttribute(pStaminaAttribute);
            addAttribute(pScoreAttribute);
            addAttribute(pMagnetXAttribute);
            addAttribute(pMagnetYAttribute);
            
            mMagnetBox.size.width = magnetSize.width;
            mMagnetBox.size.height = magnetSize.height;
            mMagnetBox.origin.x = position.x;
            mMagnetBox.origin.y = position.y;
            
            result = true;
        }
        else
        {
            result = false;
        }
//        mScore = score;
//        mStamina = stamina;
        mStanimaReduce = staminaReduce;
        
        result = true;
    }
    else
        result = false;
    
    return result;
}
void Player::updatePosition(float dt)
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    float xSpeed = getAttributeValueByKey(AttributeType::SPEED_X);
    float ySpeed = getAttributeValueByKey(AttributeType::SPEED_Y);
    
    if (this->getPositionX() + dt * xSpeed < origin.x + mCollisionBox.size.width/2 ) {
        this->setPositionX(origin.x + mCollisionBox.size.width/2);
    }
    else
    {
        if (this->getPositionX() + dt * xSpeed > visibleSize.width - mCollisionBox.size.width/2) {
            this->setPositionX(visibleSize.width - mCollisionBox.size.width/2);
        }
        else
        {
            //mPosition.x = mPosition.x + dt * xSpeed;
            this->setPositionX(this->getPositionX() + dt * xSpeed);
        }
    }
    if (this->getPositionY() + dt * ySpeed < origin.y) {
        mAlive = false;
        this->setVisible(false);
    }
    else
        this->setPositionY(this->getPositionY() + dt * ySpeed);
    
    
    float xSize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_X);
    float ySize = getAttributeValueByKey(AttributeType::COLLISION_SIZE_Y);
    mCollisionBox.origin.x = this->getPositionX();
    mCollisionBox.origin.y = this->getPositionY();
    
    mMagnetBox.origin.x = this->getPositionX();
    mMagnetBox.origin.y = this->getPositionY();
    
}
Player::~Player()
{
    
}

void Player::update(float dt)
{
    updatePosition(dt);
    updateAttribute(dt);
}

void Player::onCollision(IDisplayObject *pCollisionTarget)
{
    
}

void Player::addTouchEffect(TouchDirection dir)
{
    std::string id;
    int idnum;
    BaseEffect * effect;
    
    if (dir == TouchDirection::LEFT) {
        idnum = (int)EffectType::LEFTTOUCH + EFFECTIDBASE;
    }
    if (dir == TouchDirection::RIGHT) {
        idnum = (int)EffectType::RIGHTTOUCH + EFFECTIDBASE;
    }
    
    id = CommonUtil::itos(idnum);
    
    int priority = atoi(CommonUtil::getPropById(id, "priority").c_str());
    
    AttributeType attributekey = (AttributeType)atoi(CommonUtil::getPropById(id, "attributekey").c_str());
    
    float starttime = atof(CommonUtil::getPropById(id, "starttime").c_str());
    
    float durationtime = atof(CommonUtil::getPropById(id, "durationtime").c_str());
    
    float value = atof(CommonUtil::getPropById(id, "value").c_str());
    //effect numtype
    EffectNumType enumtype = (EffectNumType)atoi(CommonUtil::getPropById(id, "enumtype").c_str());
    //
    EffectInstantType  einstanttype = (EffectInstantType)atoi(CommonUtil::getPropById(id, "instantable").c_str());
    //effect的type类型
    EffectType type = (EffectType)atoi(CommonUtil::getPropById(id, "type").c_str());
    
    if (einstanttype == EffectInstantType::INSTANT) {
        effect = InstantEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
    }
    else
        effect = DurationEffect::create(priority, attributekey, starttime, durationtime, value, enumtype);
    
    //effect->retain();
    
    this->addEffect(effect);
}

