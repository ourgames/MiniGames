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
    if (mBaseBlockArray.empty()) {
        mBaseBlockArray.reserve(MAXSIZE);
    }
    mDisTimer = 0;
    mTimTimer = 0;
    setArray();
}

BlockManager::~BlockManager()
{
    mChanceArray.clear();
    mGenerateNumArray.clear();
    mBaseBlockArray.clear();
}

void BlockManager::setArray()
{
    int num = BLOCKTYPENUM;
    for (int i = 0; i < num; i++) {
        int id = i + BLOCKIDBASE;
        std::string blockid = CommonUtil::itos(id);
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
    int i = 0;
    for (; i < BLOCKTYPENUM; i++) {
        if (randNum >= tempNum && randNum < tempNum + mChanceArray.at(i)) {
            res = (BlockType)(i);
            break;
        }
        else
            tempNum += mChanceArray.at(i);
    }
    return res;
}

void BlockManager::generateBlock(cocos2d::Node * render_node)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    BlockType type = generateBlockType();
    cocos2d::Vec2 position;
    
    int num = mGenerateNumArray.at((int)type);
    
    if (type == BlockType::NormalBlock && num == TRACKNUM - 1) {
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
//                position.x = origin.x + visibleSize.width/2;
//                position.y = origin.y + visibleSize.height/2;
                
                BaseBlock * blockobj = BaseBlock::create(type, position);
                render_node->addChild(blockobj,1);
                mBaseBlockArray.pushBack(blockobj);
            }
        }
    }
    else if(num == 1)
    {
        int ix;
        if (type == BlockType::BigBlock)
        {
            ix = rand() % TRACKNUM - 1;
        }
        else
        {
            ix = rand() % TRACKNUM;
        }
        position.x = origin.x + (ix+1) * TRACKWIDTH;
        position.y = origin.y + visibleSize.height;
        
        BaseBlock * blockobj = BaseBlock::create(type, position);
        render_node->addChild(blockobj,1);
        mBaseBlockArray.pushBack(blockobj);
    }
}

void BlockManager::removeBlock(BaseBlock *pBaseBlock)
{
    if (pBaseBlock) {
        if (!mBaseBlockArray.empty()) {
            ssize_t index = mBaseBlockArray.getIndex(pBaseBlock);
            mBaseBlockArray.erase(index);
        }
    }
}

void BlockManager::updateBaseBlockPosition(float dt)
{
    cocos2d::Vector<BaseBlock *> toRemoveBaseBlockArray;
    if (!mBaseBlockArray.empty()) {
        for (int i = 0; i < mBaseBlockArray.size(); i++) {
            auto pBaseBlock = mBaseBlockArray.at(i);
            pBaseBlock->update(dt);
            if (!pBaseBlock->getAlive()) {
                toRemoveBaseBlockArray.pushBack(pBaseBlock);
            }
        }
    }
    for (int j = 0; j < toRemoveBaseBlockArray.size(); j++) {
        auto pToRemoveBaseBlockArray = toRemoveBaseBlockArray.at(j);
        removeBlock(pToRemoveBaseBlockArray);
    }
}

void BlockManager::testCollision(IDisplayObject *pCollisionTarget)
{
    if (!mBaseBlockArray.empty()) {
        for (int i = 0; i < mBaseBlockArray.size(); i++) {
            auto pBaseBlock = mBaseBlockArray.at(i);
            pBaseBlock->onCollision(pCollisionTarget);
        }
    }
}

void BlockManager::testAvoid(IDisplayObject *pCollisionTarget)
{
    if (!mBaseBlockArray.empty()) {
        for (int i = 0; i < mBaseBlockArray.size(); i++) {
            auto pBaseBlock = mBaseBlockArray.at(i);
            pBaseBlock->onAvoid(pCollisionTarget);
        }
    }    
}

void BlockManager::update(float dt,cocos2d::Node * render_node)
{
    mDisTimer += dt * COURCESPEED;
    mTimTimer += dt;
    
    updateBaseBlockPosition(dt);
    
    if (mDisTimer >= BlockDistance) {
        mDisTimer = mDisTimer - BlockDistance;
        //生成障碍
        generateBlock(render_node);
    }
    
    //障碍生成距离隔一段时间缩短一段距离，缩短到最小时不能再减
    if (mTimTimer >= BLOCKTIME) {
        mTimTimer = mTimTimer - BLOCKTIME;
        if (BlockDistance - BLOCKREDUCE >= BLOCKCREATEDISTANCE) {
            BlockDistance = BlockDistance - BLOCKREDUCE;
        }
        else
            BlockDistance = BLOCKCREATEDISTANCE;
    }
}