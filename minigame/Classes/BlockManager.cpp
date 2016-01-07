//
//  BlockManager.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/5.
//
//

#include "BlockManager.hpp"
//#include "Block.hpp"
#include "Movement.h"
#include "GameLayerVar.h"
//#include "Track.hpp"

BlockManager::BlockManager()
{
    blockcreatechance = new int[7];
    //初始化，后续读表设置 block_create_chance=[30,15,15,10,10,5,15]
    blockcreatechance[0] = 30;
    blockcreatechance[1] = 15;
    blockcreatechance[2] = 15;
    blockcreatechance[3] = 10;
    blockcreatechance[4] = 10;
    blockcreatechance[5] = 5;
    blockcreatechance[6] = 15;
    
    initDict();
    
    blockCreateDistance = 200;
    blockDistance = 400;
    blockTime = 1000;
    blockReduce = 50;
    
    blocklist = CCArray::createWithCapacity(MAX_COUNT);
    blocklist->retain();
}


//CCDictionary * BlockManager::initDict()
void BlockManager::initDict()
{
    dict = CCDictionary::create();
    
//    CCDictionary * dict1 = CCDictionary::create();
//    //读配置文件
//    for (int i = 0; i < BlockNum; i++) {
//        //根据id读取数值
//        CCDictionary * dict1 = CCDictionary::create();
//        int * efflistvalue = new int[10];
//    }
    //自己设置
    
    CCDictionary * dict1 = CCDictionary::create();
    
    //int array1[10] = {1,6};
    //CCInteger array1[10] = {1,6};
    CCArray * array1 = CCArray::createWithCapacity(10);
    CCInteger * array1_1 = CCInteger::create(1);
    CCInteger * array1_2 = CCInteger::create(6);
    array1->addObject(array1_1);
    array1->addObject(array1_2);
    //ccArray;
    
    //std::string filename1 = "cloud.png";
    CCString * filename1 = CCString::create("cloud.png");
    
//    float _width1 = 65;
//    float _height1 = 65;
    CCFloat * _width1 = CCFloat::create(65);
    CCFloat * _height1 = CCFloat::create(65);
    
//    int windex1 = 0;
//    int hindex1 = 0;
    CCInteger * windex1 = CCInteger::create(0);
    CCInteger * hindex1 = CCInteger::create(0);
    
    MoveMent * mvud1 = MoveMent::create(0,true,1,50);//上下，可动，下，50
    MoveMent * mvlr1 = MoveMent::create(1,false,0,0);
    
    //int createnum1 = 4;
    CCInteger *createnum1 = CCInteger::create(BlockCreateNumber[0]);
    
    dict1->setObject(array1, "efflist");
    dict1->setObject(filename1, "filename");
    
    dict1->setObject(_width1, "width");
    dict1->setObject(_height1, "height");
    
    dict1->setObject(windex1, "windex");
    dict1->setObject(hindex1, "hindex");
    
    dict1->setObject(mvud1, "movementud");
    dict1->setObject(mvlr1, "movementlr");
    
    dict1->setObject(createnum1, "createnum");
    
    //dict->setObject(dict1, "normalblock");
    dict->setObject(dict1, 0);
    dict->retain();
    //return dict;
}

void BlockManager::initEffectDict()
{
    effectdict = CCDictionary::create();
    
    //    CCDictionary * dict1 = CCDictionary::create();
    //    //读配置文件
    //    for (int i = 0; i < BlockNum; i++) {
    //        //根据id读取数值
    //        CCDictionary * dict1 = CCDictionary::create();
    //        int * efflistvalue = new int[10];
    //    }
    //自己设置
    
    CCDictionary * dict1 = CCDictionary::create();
    
    CCInteger * effectobject1 = CCInteger::create(0);
    CCInteger * effectproperty1 = CCInteger::create(0);
    CCFloat * value1 = CCFloat::create(80);
    CCFloat * effecttime1 = CCFloat::create(100);
    
    dict1->setObject(effectobject1, "effobj");
    dict1->setObject(effectproperty1, "effproperty");
    dict1->setObject(value1, "value");
    dict1->setObject(effecttime1, "effecttime");
    
    
    CCDictionary * dict2 = CCDictionary::create();
    
    CCInteger * effectobject2 = CCInteger::create(0);
    CCInteger * effectproperty2 = CCInteger::create(0);
    CCFloat * value2 = CCFloat::create(80);
    CCFloat * effecttime2 = CCFloat::create(100);
    
    dict2->setObject(effectobject2, "effobj");
    dict2->setObject(effectproperty2, "effproperty");
    dict2->setObject(value2, "value");
    dict2->setObject(effecttime2, "effecttime");
    
    CCDictionary * dict3 = CCDictionary::create();
    
    CCInteger * effectobject3 = CCInteger::create(0);
    CCInteger * effectproperty3 = CCInteger::create(0);
    CCFloat * value3 = CCFloat::create(80);
    CCFloat * effecttime3 = CCFloat::create(100);
    
    dict3->setObject(effectobject3, "effobj");
    dict3->setObject(effectproperty3, "effproperty");
    dict3->setObject(value3, "value");
    dict3->setObject(effecttime3, "effecttime");
    
    
    CCDictionary * dict4 = CCDictionary::create();
    
    CCInteger * effectobject4 = CCInteger::create(0);
    CCInteger * effectproperty4 = CCInteger::create(0);
    CCFloat * value4 = CCFloat::create(80);
    CCFloat * effecttime4 = CCFloat::create(100);
    
    dict4->setObject(effectobject4, "effobj");
    dict4->setObject(effectproperty4, "effproperty");
    dict4->setObject(value4, "value");
    dict4->setObject(effecttime4, "effecttime");
    
    
    
    
    
    
    dict->setObject(dict1, 0);
    
    dict->retain();
    //return dict;
}

//BlockType BlockManager::getCreateBlockType()
//{
//    
//    int randNum = rand() % 100 + 1;
//    int tempNum = 1;
//    for (int i = 0; i < BlockNum; i++) {
//        if (randNum >= tempNum && randNum < tempNum + blockcreatechance[i]) {
//            return (BlockType)(i);
//        }
//        else
//            tempNum += blockcreatechance[i];
//    }
//}

int BlockManager::getCreateBlockType()
{
    
    int randNum = rand() % 100 + 1;
    int tempNum = 1;
    for (int i = 0; i < BlockNum; i++) {
        if (randNum >= tempNum && randNum < tempNum + blockcreatechance[i]) {
            //return i;
            return 0;
        }
        else
            tempNum += blockcreatechance[i];
    }
}

Block * BlockManager::createBlock()
{
      int bt;
//    //根据获取的障碍类型获得对应的数值参数
//    Block * bl = Block::create();
//    bl->retain();
//    //CCDictionary * blockproer = (CCDictionary *)dict->objectForKey(bt);
//    CCDictionary * blockproer = (CCDictionary *)dict->objectForKey(0);
//    //设置effctlist
//    bl->setEffectlist((CCArray * )(blockproer->objectForKey("efflist")));
//    //设置文件名
//    CCString * fi = dynamic_cast<CCString*>(blockproer->objectForKey("filename"));
//    bl->setFilename(fi->getCString());
//    //添加精灵节点
//    bl->addActor();
//    //设置大小
//    bl->setWidth(dynamic_cast<CCFloat *>(blockproer->objectForKey("width"))->getValue());
//    bl->setHeight(dynamic_cast<CCFloat*>(blockproer->objectForKey("height"))->getValue());
//    //设置位置
//    int ix = rand() % 4;
//    int iy = rand() % 5;
//    bl->setW_index(ix);
//    bl->setH_index(iy);
//    //设置运动
//    MoveMent * objmv = dynamic_cast<MoveMent *>(blockproer->objectForKey("movementud"));
//    Movement mvstrut= {objmv->getType(),objmv->getEnable(),objmv->getDirection(),objmv->getSpeed()};
//    bl->setMoveUpDown(mvstrut);
//    
//    MoveMent * objmv2 = dynamic_cast<MoveMent *>(blockproer->objectForKey("movementlr"));
//    Movement mvstrut2= {objmv2->getType(),objmv2->getEnable(),objmv2->getDirection(),objmv2->getSpeed()};
//    bl->setMoveUpDown(mvstrut2);
    
    //根据获取的障碍类型获得对应的数值参数
    Block * bl = Block::create();
    bl->retain();
//    for (int i = 0; i < BlockCreateNumber[bt]; i++) {
//        //根据获取的障碍类型获得对应的数值参数
//        Block * bl = Block::create();
       
        //CCDictionary * blockproer = (CCDictionary *)dict->objectForKey(bt);
        CCDictionary * blockproer = (CCDictionary *)dict->objectForKey(0);
        //设置effctlist
        bl->setEffectlist((CCArray * )(blockproer->objectForKey("efflist")));
        //设置文件名
        CCString * fi = dynamic_cast<CCString*>(blockproer->objectForKey("filename"));
        bl->setFilename(fi->getCString());
        //添加精灵节点
        bl->addActor();
        //设置大小
        bl->setWidth(dynamic_cast<CCFloat *>(blockproer->objectForKey("width"))->getValue());
        bl->setHeight(dynamic_cast<CCFloat*>(blockproer->objectForKey("height"))->getValue());
        //设置位置
        int ix = rand() % 5;
        int iy = rand() % 4;
        bl->setW_index(ix);
        bl->setH_index(iy);
        //设置运动
        MoveMent * objmv = dynamic_cast<MoveMent *>(blockproer->objectForKey("movementud"));
        Movement mvstrut= {objmv->getType(),objmv->getEnable(),objmv->getDirection(),objmv->getSpeed()};
        bl->setMoveUpDown(mvstrut);
        
        MoveMent * objmv2 = dynamic_cast<MoveMent *>(blockproer->objectForKey("movementlr"));
        Movement mvstrut2= {objmv2->getType(),objmv2->getEnable(),objmv2->getDirection(),objmv2->getSpeed()};
        bl->setMoveLeftRight(mvstrut2);
//    }
    return bl;
    //
    //
}

//Block * BlockManager::createBlockNormal()
//{
//    int bt;
//    //根据获取的障碍类型获得对应的数值参数
//    Block * bl = Block::create();
//    bl->retain();
//    //    for (int i = 0; i < BlockCreateNumber[bt]; i++) {
//    //        //根据获取的障碍类型获得对应的数值参数
//    //        Block * bl = Block::create();
//    
//    //CCDictionary * blockproer = (CCDictionary *)dict->objectForKey(bt);
//    CCDictionary * blockproer = (CCDictionary *)dict->objectForKey(0);
//    //设置effctlist
//    bl->setEffectlist((CCArray * )(blockproer->objectForKey("efflist")));
//    //设置文件名
//    CCString * fi = dynamic_cast<CCString*>(blockproer->objectForKey("filename"));
//    bl->setFilename(fi->getCString());
//    //添加精灵节点
//    bl->addActor();
//    //设置大小
//    bl->setWidth(dynamic_cast<CCFloat *>(blockproer->objectForKey("width"))->getValue());
//    bl->setHeight(dynamic_cast<CCFloat*>(blockproer->objectForKey("height"))->getValue());
//    //设置位置
//    int ix = rand() % 4;
//    int iy = rand() % 5;
//    bl->setW_index(ix);
//    bl->setH_index(iy);
//    //设置运动
//    MoveMent * objmv = dynamic_cast<MoveMent *>(blockproer->objectForKey("movementud"));
//    Movement mvstrut= {objmv->getType(),objmv->getEnable(),objmv->getDirection(),objmv->getSpeed()};
//    bl->setMoveUpDown(mvstrut);
//    
//    MoveMent * objmv2 = dynamic_cast<MoveMent *>(blockproer->objectForKey("movementlr"));
//    Movement mvstrut2= {objmv2->getType(),objmv2->getEnable(),objmv2->getDirection(),objmv2->getSpeed()};
//    bl->setMoveUpDown(mvstrut2);
//    //    }
//    return bl;
//    //
//    //
//}

Block * BlockManager::createClone(Block *obj)
{
    
}
void BlockManager::createManager()
{
    int crnm =BlockCreateNumber[getCreateBlockType()];
    
    if (crnm == 4) {
        //
        Block * block1 = createBlock();
        Block * block2 = createBlock();
        Block * block3 = createBlock();
        Block * block4 = createBlock();
        
        CCArray * bkarr = CCArray::createWithCapacity(4);
        bkarr->retain();
        
        bkarr->addObject(block1);
        bkarr->addObject(block2);
        bkarr->addObject(block3);
        bkarr->addObject(block4);
        
        int ix = rand() % 5;
        int iy = rand() % 4;
        
        block1->setH_index(iy);
        block2->setH_index(iy);
        block3->setH_index(iy);
        block4->setH_index(iy);
        
        Block * obj;
        int j = 0;
        for (int i = 0; i < 5; i++) {
            if (i == ix) {
                continue;
            }
            else
            {
                obj = dynamic_cast<Block* >(bkarr->getObjectAtIndex(j));
                obj->setAnchorPoint(ccp(0,0));
                obj->setScale(0.75,1.0);
                obj->setW_index(i);
                j++;
                blocklist->addObject(obj);
            }
        }
        bkarr->removeAllObjects();
        CC_SAFE_RELEASE_NULL(bkarr);
        
    }
    else
    {
        Block * block = createBlock();
        Sprite * blockactor =dynamic_cast<Sprite*>(block->getActor());
        blockactor->setAnchorPoint(ccp(0,0));
        blockactor->setScale(0.75, 1.0);
        blocklist->addObject(blockactor);
        //blockactor->setPosition(origin.x + 40 + (block->getW_index() + (int)track.getTrackState()) * track.getCircuitWidth(), origin.y + block->getH_index() * track.getCircuitWidth() + visibleSize.height);
        //blockactor->setPosition(origin.x + 40 + (block->getW_index() + (int)track.getTrackState()) * track.getCircuitWidth(), origin.y + block->getH_index() * track.getCircuitWidth() * 0.5 );
        //this->addChild(block,1);
    }
}
void BlockManager::createManager(Track *track,cocos2d::Node * render_node)
{
    
    int crnm =BlockCreateNumber[getCreateBlockType()];
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if (crnm == 4) {
        //
        Block * block1 = createBlock();
        Block * block2 = createBlock();
        Block * block3 = createBlock();
        Block * block4 = createBlock();
        
        CCArray * bkarr = CCArray::createWithCapacity(4);
        bkarr->retain();
        
        bkarr->addObject(block1);
        bkarr->addObject(block2);
        bkarr->addObject(block3);
        bkarr->addObject(block4);
        
        int ix = rand() % 5;
        int iy = rand() % 4;
        
        block1->setH_index(iy);
        block2->setH_index(iy);
        block3->setH_index(iy);
        block4->setH_index(iy);
        
        Block * obj;
        int j = 0;
        for (int i = 0; i < 5; i++) {
            if (i == ix) {
                continue;
            }
            else
            {
                obj = dynamic_cast<Block* >(bkarr->getObjectAtIndex(j));
                
//                obj->setAnchorPoint(ccp(0,0));
//                obj->setScale(0.75,1.0);
                obj->setW_index(i);
                
                Sprite * blockactor =dynamic_cast<Sprite*>(obj->getActor());
                blockactor->setAnchorPoint(ccp(0,0));
                blockactor->setScale(0.75, 1.0);
                blockactor->setPosition(origin.x + 20 + (obj->getW_index() + (int)track->getTrackState()) * track->getCircuitWidth(), origin.y + obj->getH_index() * track->getCircuitWidth() * 0.5 + visibleSize.height );
                //render_node->addChild(blockactor,1);
                render_node->addChild(obj,1);
                
                blocklist->addObject(obj);
                j++;
            }
        }
        bkarr->removeAllObjects();
        CC_SAFE_RELEASE_NULL(bkarr);
        
    }
    else
    {
        Block * block = createBlock();
        Sprite * blockactor =dynamic_cast<Sprite*>(block->getActor());
        blockactor->setAnchorPoint(ccp(0,0));
        blockactor->setScale(0.75, 1.0);
        blockactor->setPosition(origin.x + 40 + (block->getW_index() + (int)track->getTrackState()) * track->getCircuitWidth(), origin.y + block->getH_index() * track->getCircuitWidth() * 0.5 + visibleSize.height);
        render_node->addChild(blockactor);
        blocklist->addObject(blockactor);
        //blockactor->setPosition(origin.x + 40 + (block->getW_index() + (int)track.getTrackState()) * track.getCircuitWidth(), origin.y + block->getH_index() * track.getCircuitWidth() + visibleSize.height);
        //blockactor->setPosition(origin.x + 40 + (block->getW_index() + (int)track.getTrackState()) * track.getCircuitWidth(), origin.y + block->getH_index() * track.getCircuitWidth() * 0.5 );
        //this->addChild(block,1);
    }

}

void BlockManager::displayBlock(Track *track,cocos2d::Node * render_node)
{
    int count = blocklist->count();
    Ref * obj;
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    CCARRAY_FOREACH(blocklist, obj){
        Block * block = (Block *)obj;
        Sprite * blockactor =dynamic_cast<Sprite*>(block->getActor());
        blockactor->setAnchorPoint(ccp(0,0));
        blockactor->setScale(0.75, 1.0);
        blockactor->setPosition(origin.x + 40 + (block->getW_index() + (int)track->getTrackState()) * track->getCircuitWidth(), origin.y + block->getH_index() * track->getCircuitWidth() * 0.5 );
        render_node->addChild(blockactor);
    }
}

void BlockManager::blockMove(Track *track, cocos2d::Node *render_node)
{
    Ref * obj;
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CCARRAY_FOREACH(blocklist, obj){
        
        Block * block = (Block *)obj;
        Sprite * blockactor =dynamic_cast<Sprite*>(block->getActor());

        if (block->isAlive()) {// 活着
            if (block->getMoveUpDown().enable) {//上下可动
                switch (block->getMoveUpDown().direction) {
                    case 0://上
                        blockactor->setPositionY(blockactor->getPositionY() + block->getMoveUpDown().speed);
                        if (blockactor->getPositionY()  >= visibleSize.height) {
                            block->setIsActive(false);
                        }
                        
                        break;
                    case 1://下
                        blockactor->setPositionY(blockactor->getPositionY() - block->getMoveUpDown().speed);
                        if (blockactor->getPositionY() + blockactor->getContentSize().height <= 0) {
                            block->setIsActive(false);
                        }
                    default:
                        break;
                }
                
            }
            if (block->getMoveLeftRight().enable) {
                switch (block->getMoveLeftRight().direction) {
                    case 0://左
                        blockactor->setPositionX(blockactor->getPositionX() - block->getMoveLeftRight().speed);
                        if (blockactor->getPositionX() + blockactor->getContentSize().width <= 0) {
                            block->setIsActive(false);
                        }
                        break;
                    case 1://右
                        blockactor->setPositionX(blockactor->getPositionX() + block->getMoveLeftRight().speed);
                        if (blockactor->getPositionX()  >= visibleSize.width) {
                            block->setIsActive(false);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        
    }
}

BlockManager::~BlockManager()
{
    delete [] blockcreatechance;
    dict->release();
    
    blocklist->removeAllObjects();
    CC_SAFE_RELEASE_NULL(blocklist);
}
















