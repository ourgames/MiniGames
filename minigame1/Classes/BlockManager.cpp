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
    if (mTrackBlockArray.empty()) {
        mTrackBlockArray.reserve(MAXSIZE);
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
    mTrackBlockArray.clear();
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

void BlockManager::addTouchEffect(TouchDirection dir)
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

    if (!mTrackBlockArray.empty()) {
        for (int i = 0; i < mTrackBlockArray.size(); i++) {
            auto pBaseBlock = mTrackBlockArray.at(i);
            pBaseBlock->addEffect(effect);
            
        }
    }
    
}


void BlockManager::generateBlock(cocos2d::Node * render_node)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    BlockType type = generateBlockType();
    cocos2d::Vec2 position;
   
    type = BlockType::DizzyBlock;
    
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
        
        if (type == BlockType::TrackBlock) {
            mTrackBlockArray.pushBack(blockobj);
        }
        else mBaseBlockArray.pushBack(blockobj);
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

void BlockManager::removeTrackBlock(BaseBlock *pBaseBlock)
{
    if (pBaseBlock) {
        if (!mBaseBlockArray.empty()) {
            ssize_t index = mTrackBlockArray.getIndex(pBaseBlock);
            mTrackBlockArray.erase(index);
        }
    }
}

void BlockManager::updateBaseBlockPosition(float dt)
{
    cocos2d::Vector<BaseBlock *> toRemoveBaseBlockArray;
    cocos2d::Vector<BaseBlock *> toRemoveTrackBlockArray;
    
    if (!mBaseBlockArray.empty()) {
        for (int i = 0; i < mBaseBlockArray.size(); i++) {
            auto pBaseBlock = mBaseBlockArray.at(i);
            pBaseBlock->update(dt);
            if (!pBaseBlock->getAlive()) {
                toRemoveBaseBlockArray.pushBack(pBaseBlock);
            }
        }
    }
    if (!mTrackBlockArray.empty()) {
        for (int i = 0; i < mTrackBlockArray.size(); i++) {
            auto pBaseBlock = mTrackBlockArray.at(i);
            pBaseBlock->update(dt);
            if (!pBaseBlock->getAlive()) {
                toRemoveTrackBlockArray.pushBack(pBaseBlock);
            }
        }
    }
    
    for (int j = 0; j < toRemoveBaseBlockArray.size(); j++) {
        auto pToRemoveBaseBlock = toRemoveBaseBlockArray.at(j);
        removeBlock(pToRemoveBaseBlock);
    }
    
    for (int j = 0; j < toRemoveTrackBlockArray.size(); j++) {
        auto pToRemoveBaseBlock = toRemoveTrackBlockArray.at(j);
        removeTrackBlock(pToRemoveBaseBlock);
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
    if (!mTrackBlockArray.empty()) {
        for (int i = 0; i < mTrackBlockArray.size(); i++) {
            auto pBaseBlock = mTrackBlockArray.at(i);
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
    if (!mTrackBlockArray.empty()) {
        for (int i = 0; i < mTrackBlockArray.size(); i++) {
            auto pBaseBlock = mTrackBlockArray.at(i);
            pBaseBlock->onAvoid(pCollisionTarget);
        }
    }
    
    
}

void BlockManager::update(float dt,cocos2d::Node * render_node,IDisplayObject *pCollisionTarget)
{
    mDisTimer += dt * COURCESPEED;
    mTimTimer += dt;
    
    updateBaseBlockPosition(dt);
    
    testCollision(pCollisionTarget);
    testAvoid(pCollisionTarget);
    
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