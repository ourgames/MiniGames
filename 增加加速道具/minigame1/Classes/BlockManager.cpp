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
//读表生成概率数组
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
//根据概率数组生成一种道具
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

//一次生成道具
//void BlockManager::generateBlock(cocos2d::Node * render_node)
void BlockManager::generateBlock(IDisplayObject * render_node)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    BlockType type = generateBlockType();
    cocos2d::Vec2 position;
   
    //type = BlockType::DizzyBlock;
    
    int num = mGenerateNumArray.at((int)type);
    
    //普通障碍一次生成一排四个
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
                position.y = origin.y + visibleSize.height - render_node->getPositionY();
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
        position.y = origin.y + visibleSize.height - render_node->getPositionY();
        
        BaseBlock * blockobj = BaseBlock::create(type, position);
        render_node->addChild(blockobj,1);
        
        if (type == BlockType::TrackBlock) {
            mTrackBlockArray.pushBack(blockobj);
        }
        else mBaseBlockArray.pushBack(blockobj);
    }
}
//删除已经失效的常规障碍
void BlockManager::removeBlock(BaseBlock *pBaseBlock)
{
    if (pBaseBlock) {
        if (!mBaseBlockArray.empty()) {
            ssize_t index = mBaseBlockArray.getIndex(pBaseBlock);
            mBaseBlockArray.erase(index);
        }
    }
}
//删除已经失效的追踪障碍
void BlockManager::removeTrackBlock(BaseBlock *pBaseBlock)
{
    if (pBaseBlock) {
        if (!mBaseBlockArray.empty()) {
            ssize_t index = mTrackBlockArray.getIndex(pBaseBlock);
            mTrackBlockArray.erase(index);
        }
    }
}
//更新障碍的位置，并移除已经失效的障碍
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
//判断是否发生碰撞
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
//判断是否成功躲过障碍
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

//void BlockManager::update(float dt,cocos2d::Node * render_node,IDisplayObject *pCollisionTarget)
void BlockManager::update(float dt,IDisplayObject * render_node,IDisplayObject *pCollisionTarget)
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