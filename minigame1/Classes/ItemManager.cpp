//
//  ItemManager.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/25.
//
//

#include "ItemManager.hpp"

ItemManager::ItemManager()
{
    if (mChanceArray.empty()) {
        mChanceArray.reserve(ITEMTYPENUM);
    }
    if (mGenerateNumArray.empty()) {
        mGenerateNumArray.reserve(ITEMTYPENUM);
    }
    if (mItemArray.empty()) {
        mItemArray.reserve(MAXSIZE);
    }
    mDistanceVar = 0;
    setArray();
}

ItemManager::~ItemManager()
{
    mChanceArray.clear();
    mGenerateNumArray.clear();
    mItemArray.clear();
}

//读表设置相关数组值
void ItemManager::setArray()
{
    int num = ITEMTYPENUM;
    for (int i = 0; i < num; i++) {
        int id = i + ITEMIDBASE;
        std::string itemid = CommonUtil::itos(id);
        float temp = atof(CommonUtil::getPropById(itemid, "chance").c_str());
        int tep = atoi(CommonUtil::getPropById(itemid, "num").c_str());
        mChanceArray.push_back(temp);
        mGenerateNumArray.push_back(tep);
    }
}
//根据概率数组随机生成一次什么样类型的道具
ItemType ItemManager::generateItemType()
{
    ItemType res = ItemType::Coin;
    int randNum = rand() % 100 + 1;
    int tempNum = 1;
    int i = 0;
    for (; i < ITEMTYPENUM; i++) {
        if (randNum >= tempNum && randNum < tempNum + mChanceArray.at(i)) {
            res = (ItemType)(i);
            break;
        }
        else
            tempNum += mChanceArray.at(i);
    }
    
    return res;
}
//删除已经失效的道具
void ItemManager::removeItem(Item *pItem)
{
    if (pItem) {
        if (!mItemArray.empty()) {
            ssize_t index = mItemArray.getIndex(pItem);
            mItemArray.erase(index);
        }
    }
}
//更新道具位置，对于已经失效的道具从道具管理列表中移除
void ItemManager::updateItemPosition(float dt)
{
    cocos2d::Vector<Item *> toRemoveItemArray;
    
    if (!mItemArray.empty()) {
        for (int i = 0; i < mItemArray.size(); i++) {
            auto pItem = mItemArray.at(i);
            pItem->update(dt);
            if (!pItem->getAlive()) {
                toRemoveItemArray.pushBack(pItem);
            }
        }
    }
    
    for (int j = 0; j < toRemoveItemArray.size(); j++) {
        auto pToRemoveItem = toRemoveItemArray.at(j);
        removeItem(pToRemoveItem);
    }
}

//bool ItemManager::isAvaliblePosition(cocos2d::Vec2 position,BlockManager *blockmanager)
//{
//    bool result;
//    
//    if (!blockmanager->mBaseBlockArray.empty()) {
//        for (int i = 0; i < blockmanager->mBaseBlockArray.size(); i++) {
//            auto pBaseBlock = blockmanager->mBaseBlockArray.at(i);
//            
//        }
//    }
//}
//随机生成一次道具
void ItemManager::generateItem(cocos2d::Node *render_node)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ItemType type = generateItemType();
    cocos2d::Vec2 position;
    cocos2d::Vec2 positionWorld;
    
    //type = ItemType::Invicible;
    
    int ix = rand() % TRACKNUM;
    position.x = origin.x + (ix+1) * TRACKWIDTH;
    // position.y = origin.y + visibleSize.height;
    position.y = origin.y + visibleSize.height - render_node->getPositionY();
    
    
    
    Item * itemobj = Item::create(type, position);
    render_node->addChild(itemobj,1);
    //render_node->addChild(itemobj);
    mItemArray.pushBack(itemobj);
}
//判断是否发生碰撞
void ItemManager::testCollision(cocos2d::Node * render_node,IDisplayObject *pCollisionTarget)
{
    if (!mItemArray.empty()) {
        for (int i = 0; i < mItemArray.size(); i++) {
            auto pItem = mItemArray.at(i);
            pItem->onCollision(render_node,pCollisionTarget);
        }
    }
}
//对生成的道具列表进行更新管理
void ItemManager::update(float dt, cocos2d::Node *render_node, IDisplayObject *pCollisionTarget)
{
    mDistanceVar += dt * COURCESPEED;
    
    updateItemPosition(dt);
    
    testCollision(render_node,pCollisionTarget);
    
    if (mDistanceVar >= ITEMDISTANCE) {
        mDistanceVar = mDistanceVar - ITEMDISTANCE;
        generateItem(render_node);
    }
}




