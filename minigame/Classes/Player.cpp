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
        //return true;
    }
    return true;
}
//bool Player::addActor()
//{
////    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
////    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
////    //actor = Sprite::create(filename);
//    actor = Sprite::createWithSpriteFrameName(getFilename());
//    actor->retain();
//    this->addChild(dynamic_cast<Sprite*>(actor));
//}
//Player * Player::createPlayer(Track *track,cocos2d::Node * render_node)
//Player * Player::createPlayer(Track *track)
//{
//    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
//    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    
//    Player * player = Player::create();
//    player->retain();
//    
//    player->setFilename("xiabai.jpg");
//    Node * playeractor = getActor();
//    playeractor = Sprite::create(filename);
//    playeractor->setAnchorPoint(ccp(0,0));
//    playeractor->setScale(0.3, 0.3);
//    player->setPosition(origin.x + 20 + track->getCircuitWidth() * (2 + (int)track->getTrackState()), origin.y + playeractor->getContentSize().height * 0.3/2);
//    
//    player->addChild(playeractor);
//    
//    return player;
//    //player->addActor();
//    
//}