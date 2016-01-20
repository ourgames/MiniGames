//
//  BlockManager.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/20.
//
//

#include "BlockManager.hpp"

BlockManager::BlockManager()
{
    if (mChanceArray.empty()) {
        mChanceArray.reserve(BLOCKTYPENUM);
    }
    if (mGenerateNumArray.empty()) {
        mGenerateNumArray.reserve(BLOCKTYPENUM);
    }
    distimer = 0;
    timtimer = 0;
}

BlockManager::~BlockManager()
{
    mChanceArray.clear();
    mGenerateNumArray.clear();
}

void BlockManager::setArray()
{
    for (int i = 0; i < BLOCKTYPENUM; i++) {
        std::string blockid = CommonUtil::itos(i + BLOCKIDBASE);
        float temp = atof(CommonUtil::getPropById(blockid, "chance").c_str());
        int tep = atoi(CommonUtil::getPropById(blockid, "num").c_str());
        mChanceArray.push_back(temp);
        mGenerateNumArray.push_back(tep);
    }
}
BlockType BlockManager::generateBlockType()
{
    BlockType res = BlockType::NormalBlock;
    int randNum = rand() % 100 + 1;
    int tempNum = 1;
    for (int i = 0; i < BLOCKTYPENUM; i++) {
        if (randNum >= tempNum && randNum < tempNum + mChanceArray.at(i)) {
            res = (BlockType)(i);
            //return 0;
        }
        else
            tempNum += mChanceArray.at(i);
    }
    return res;
}

void BlockManager::generateBlock()
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    BlockType type = generateBlockType();
    cocos2d::Vec2 position;
    cocos2d::Size collisionSize;
    cocos2d::Vec2 speed;
    float score;
    float stamina;
    float time;
    std::string filename;
    
    
    int num = mGenerateNumArray.at((int)type);
    
    std::string blockid = CommonUtil::itos((int)type + BLOCKIDBASE);
    
    if (type == BlockType::NormalBlock) {
        int ix = rand() % TRACKNUM;
        for (int i = 0; i < TRACKNUM; i++) {
            if (i == ix) {
                continue;
            }
            else
            {
                //位置信息
                position.x = origin.x + (i+1) * TRACKWIDTH;
                position.y = origin.y + visibleSize.height;
                //碰撞盒信息
                std::string collision = CommonUtil::getPropById(blockid, "collision");
                CCArray * colli = CommonUtil::split(collision.c_str(), ",");
                collisionSize.width = (dynamic_cast<CCString*>(colli->getObjectAtIndex(0)))->floatValue();
                collisionSize.height = (dynamic_cast<CCString*>(colli->getObjectAtIndex(1)))->floatValue();
                //速度信息
                std::string speedstr = CommonUtil::getPropById(blockid, "speed");
                speedstr.erase(0,1);
                speedstr.erase(speedstr.end()-1, speedstr.end());
                CCArray * speedli = CommonUtil::split(speedstr.c_str(), ",");
                speed.x = (dynamic_cast<CCString*>(speedli->getObjectAtIndex(0)))->floatValue();
                speed.y = (dynamic_cast<CCString*>(speedli->getObjectAtIndex(1)))->floatValue();
                
            }
        }
    }
}

void BlockManager::update(float dt)
{
    distimer += dt * COURCESPEED;
    timtimer += dt;
    
    if (distimer >= BlockDistance) {
        distimer = distimer - BlockDistance;
        //生成障碍
        generateBlock();
    }
    //障碍生成距离隔一段时间缩短一段距离，缩短到最小时不能再减
    if (timtimer >= BLOCKTIME) {
        timtimer = timtimer - BLOCKTIME;
        if (BlockDistance - BLOCKREDUCE >= BLOCKCREATEDISTANCE) {
            BlockDistance = BlockDistance - BLOCKREDUCE;
        }
        else
            BlockDistance = BLOCKCREATEDISTANCE;
    }
}