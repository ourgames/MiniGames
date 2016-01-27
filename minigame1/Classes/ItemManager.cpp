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

void ItemManager::removeItem(Item *pItem)
{
    if (pItem) {
        if (!mItemArray.empty()) {
            ssize_t index = mItemArray.getIndex(pItem);
            mItemArray.erase(index);
        }
    }
}
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

void ItemManager::generateItem(cocos2d::Node *render_node)
{
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ItemType type = generateItemType();
    cocos2d::Vec2 position;
    
    //type = ItemType::Invicible;
    
    int ix = rand() % TRACKNUM;
    position.x = origin.x + (ix+1) * TRACKWIDTH;
    position.y = origin.y + visibleSize.height;
    
    Item * itemobj = Item::create(type, position);
    render_node->addChild(itemobj,1);
    mItemArray.pushBack(itemobj);
}

void ItemManager::testCollision(IDisplayObject *pCollisionTarget)
{
    if (!mItemArray.empty()) {
        for (int i = 0; i < mItemArray.size(); i++) {
            auto pItem = mItemArray.at(i);
            pItem->onCollision(pCollisionTarget);
        }
    }
}

void ItemManager::update(float dt, cocos2d::Node *render_node, IDisplayObject *pCollisionTarget)
{
    mDistanceVar += dt * COURCESPEED;
    
    updateItemPosition(dt);
    
    testCollision(pCollisionTarget);
    
    if (mDistanceVar >= ITEMDISTANCE) {
        mDistanceVar = mDistanceVar - ITEMDISTANCE;
        generateItem(render_node);
    }
}




