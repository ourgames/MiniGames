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
    CCInteger * array1_1 = CCInteger::create(0);
    //CCInteger * array1_2 = CCInteger::create(6);
    array1->addObject(array1_1);
    //array1->addObject(array1_2);
    //ccArray;
    
    //std::string filename1 = "cloud.png";
    CCString * filename1 = CCString::create("cloud.png");
    
//    float _width1 = 65;
//    float _height1 = 65;
    CCFloat * _width1 = CCFloat::create(1);
    CCFloat * _height1 = CCFloat::create(1);
    
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
    
    
    
    CCDictionary * dict2 = CCDictionary::create();
    CCArray * array2 = CCArray::createWithCapacity(10);
    CCInteger * array2_1 = CCInteger::create(1);
    array2->addObject(array2_1);
    CCString * filename2 = CCString::create("building_1.png");
    CCFloat * _width2 = CCFloat::create(2);
    CCFloat * _height2 = CCFloat::create(2);
    CCInteger * windex2 = CCInteger::create(0);
    CCInteger * hindex2 = CCInteger::create(0);
    MoveMent * mvud2 = MoveMent::create(0,true,1,50);//上下，可动，下，50
    MoveMent * mvlr2 = MoveMent::create(1,false,0,0);
    
    CCInteger *createnum2 = CCInteger::create(BlockCreateNumber[1]);
    
    dict2->setObject(array2, "efflist");
    dict2->setObject(filename2, "filename");
    dict2->setObject(_width2, "width");
    dict2->setObject(_height2, "height");
    dict2->setObject(windex2, "windex");
    dict2->setObject(hindex2, "hindex");
    dict2->setObject(mvud2, "movementud");
    dict2->setObject(mvlr2, "movementlr");
    dict2->setObject(createnum2, "createnum");
    
    CCDictionary * dict3 = CCDictionary::create();
    CCArray * array3 = CCArray::createWithCapacity(10);
    CCInteger * array3_1 = CCInteger::create(2);
    CCInteger * array3_2 = CCInteger::create(7);
    array3->addObject(array3_1);
    array3->addObject(array3_2);
    CCString * filename3 = CCString::create("puff_1.png");
    CCFloat * _width3 = CCFloat::create(1);
    CCFloat * _height3 = CCFloat::create(1);
    CCInteger * windex3 = CCInteger::create(0);
    CCInteger * hindex3 = CCInteger::create(0);
    MoveMent * mvud3 = MoveMent::create(0,true,1,50);//上下，可动，下，50
    MoveMent * mvlr3 = MoveMent::create(1,false,0,0);
    
    CCInteger *createnum3 = CCInteger::create(BlockCreateNumber[2]);
    
    dict3->setObject(array3, "efflist");
    dict3->setObject(filename3, "filename");
    dict3->setObject(_width3, "width");
    dict3->setObject(_height3, "height");
    dict3->setObject(windex3, "windex");
    dict3->setObject(hindex3, "hindex");
    dict3->setObject(mvud3, "movementud");
    dict3->setObject(mvlr3, "movementlr");
    dict3->setObject(createnum3, "createnum");
    
    
    CCDictionary * dict4 = CCDictionary::create();
    CCArray * array4 = CCArray::createWithCapacity(10);
    CCInteger * array4_1 = CCInteger::create(0);
    array4->addObject(array4_1);
    CCString * filename4 = CCString::create("player_float.png");
    CCFloat * _width4 = CCFloat::create(1);
    CCFloat * _height4 = CCFloat::create(1);
    CCInteger * windex4 = CCInteger::create(0);
    CCInteger * hindex4 = CCInteger::create(0);
    MoveMent * mvud4 = MoveMent::create(0,true,1,50);//上下，可动，下，50
    MoveMent * mvlr4 = MoveMent::create(1,true,0,2);
    
    CCInteger *createnum4 = CCInteger::create(BlockCreateNumber[3]);
    
    dict4->setObject(array4, "efflist");
    dict4->setObject(filename4, "filename");
    dict4->setObject(_width4, "width");
    dict4->setObject(_height4, "height");
    dict4->setObject(windex4, "windex");
    dict4->setObject(hindex4, "hindex");
    dict4->setObject(mvud4, "movementud");
    dict4->setObject(mvlr4, "movementlr");
    dict4->setObject(createnum4, "createnum");
    
    CCDictionary * dict5 = CCDictionary::create();
    CCArray * array5 = CCArray::createWithCapacity(10);
    CCInteger * array5_1 = CCInteger::create(0);
    array5->addObject(array5_1);
    CCString * filename5 = CCString::create("player_float.png");
    CCFloat * _width5 = CCFloat::create(1);
    CCFloat * _height5 = CCFloat::create(1);
    CCInteger * windex5 = CCInteger::create(0);
    CCInteger * hindex5 = CCInteger::create(0);
    MoveMent * mvud5 = MoveMent::create(0,true,1,50);//上下，可动，下，50
    MoveMent * mvlr5 = MoveMent::create(1,true,1,2);
    
    CCInteger *createnum5 = CCInteger::create(BlockCreateNumber[4]);
    
    dict5->setObject(array5, "efflist");
    dict5->setObject(filename5, "filename");
    dict5->setObject(_width5, "width");
    dict5->setObject(_height5, "height");
    dict5->setObject(windex5, "windex");
    dict5->setObject(hindex5, "hindex");
    dict5->setObject(mvud5, "movementud");
    dict5->setObject(mvlr5, "movementlr");
    dict5->setObject(createnum5, "createnum");
    
    CCDictionary * dict6 = CCDictionary::create();
    CCArray * array6 = CCArray::createWithCapacity(10);
    CCInteger * array6_1 = CCInteger::create(0);
    array6->addObject(array6_1);
    CCString * filename6 = CCString::create("puff_2.png");
    CCFloat * _width6 = CCFloat::create(1);
    CCFloat * _height6 = CCFloat::create(1);
    CCInteger * windex6 = CCInteger::create(0);
    CCInteger * hindex6 = CCInteger::create(0);
    MoveMent * mvud6 = MoveMent::create(0,true,1,50);//上下，可动，下，50
    MoveMent * mvlr6 = MoveMent::create(1,true,0,2);
    
    CCInteger *createnum6 = CCInteger::create(BlockCreateNumber[5]);
    
    dict6->setObject(array6, "efflist");
    dict6->setObject(filename6, "filename");
    dict6->setObject(_width6, "width");
    dict6->setObject(_height6, "height");
    dict6->setObject(windex6, "windex");
    dict6->setObject(hindex6, "hindex");
    dict6->setObject(mvud6, "movementud");
    dict6->setObject(mvlr6, "movementlr");
    dict6->setObject(createnum6, "createnum");
    
    CCDictionary * dict7 = CCDictionary::create();
    CCArray * array7 = CCArray::createWithCapacity(10);
    CCInteger * array7_1 = CCInteger::create(1);
    array7->addObject(array7_1);
    CCString * filename7 = CCString::create("building_4.png");
    CCFloat * _width7 = CCFloat::create(1);
    CCFloat * _height7 = CCFloat::create(1);
    CCInteger * windex7 = CCInteger::create(0);
    CCInteger * hindex7 = CCInteger::create(0);
    MoveMent * mvud7 = MoveMent::create(0,true,1,60);//上下，可动，下，50
    MoveMent * mvlr7 = MoveMent::create(1,false,0,0);
    
    CCInteger *createnum7 = CCInteger::create(BlockCreateNumber[6]);
    
    dict7->setObject(array7, "efflist");
    dict7->setObject(filename7, "filename");
    dict7->setObject(_width7, "width");
    dict7->setObject(_height7, "height");
    dict7->setObject(windex7, "windex");
    dict7->setObject(hindex7, "hindex");
    dict7->setObject(mvud7, "movementud");
    dict7->setObject(mvlr7, "movementlr");
    dict7->setObject(createnum7, "createnum");
    
    //dict->setObject(dict1, "normalblock");
    dict->setObject(dict1, 0);
    dict->setObject(dict2, 1);
    dict->setObject(dict3, 2);
    dict->setObject(dict4, 3);
    dict->setObject(dict5, 4);
    dict->setObject(dict6, 5);
    dict->setObject(dict7, 6);
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
    CCFloat * value1 = CCFloat::create(-80);
    CCFloat * effecttime1 = CCFloat::create(0);
    
    dict1->setObject(effectobject1, "effobj");
    dict1->setObject(effectproperty1, "effproperty");
    dict1->setObject(value1, "value");
    dict1->setObject(effecttime1, "effecttime");
    
    
    CCDictionary * dict2 = CCDictionary::create();
    
    CCInteger * effectobject2 = CCInteger::create(0);
    CCInteger * effectproperty2 = CCInteger::create(0);
    CCFloat * value2 = CCFloat::create(-120);
    CCFloat * effecttime2 = CCFloat::create(0);
    
    dict2->setObject(effectobject2, "effobj");
    dict2->setObject(effectproperty2, "effproperty");
    dict2->setObject(value2, "value");
    dict2->setObject(effecttime2, "effecttime");
    
    CCDictionary * dict3 = CCDictionary::create();
    
    CCInteger * effectobject3 = CCInteger::create(0);
    CCInteger * effectproperty3 = CCInteger::create(0);
    CCFloat * value3 = CCFloat::create(-40);
    CCFloat * effecttime3 = CCFloat::create(0);
    
    dict3->setObject(effectobject3, "effobj");
    dict3->setObject(effectproperty3, "effproperty");
    dict3->setObject(value3, "value");
    dict3->setObject(effecttime3, "effecttime");
    
    
    CCDictionary * dict4 = CCDictionary::create();
    
    CCInteger * effectobject4 = CCInteger::create(0);
    CCInteger * effectproperty4 = CCInteger::create(0);
    CCFloat * value4 = CCFloat::create(100);
    CCFloat * effecttime4 = CCFloat::create(0);
    
    dict4->setObject(effectobject4, "effobj");
    dict4->setObject(effectproperty4, "effproperty");
    dict4->setObject(value4, "value");
    dict4->setObject(effecttime4, "effecttime");
    
    CCDictionary * dict5 = CCDictionary::create();
    
    CCInteger * effectobject5 = CCInteger::create(0);
    CCInteger * effectproperty5 = CCInteger::create(1);
    CCFloat * value5 = CCFloat::create(100);
    CCFloat * effecttime5 = CCFloat::create(0);
    
    dict5->setObject(effectobject5, "effobj");
    dict5->setObject(effectproperty5, "effproperty");
    dict5->setObject(value5, "value");
    dict5->setObject(effecttime5, "effecttime");
    
    
    CCDictionary * dict6 = CCDictionary::create();
    
    CCInteger * effectobject6 = CCInteger::create(1);
    CCInteger * effectproperty6 = CCInteger::create(2);
    CCFloat * value6 = CCFloat::create(50);
    CCFloat * effecttime6 = CCFloat::create(1500);
    
    dict6->setObject(effectobject6, "effobj");
    dict6->setObject(effectproperty6, "effproperty");
    dict6->setObject(value6, "value");
    dict6->setObject(effecttime6, "effecttime");
    
    CCDictionary * dict7 = CCDictionary::create();
    
    CCInteger * effectobject7 = CCInteger::create(0);
    CCInteger * effectproperty7 = CCInteger::create(3);
    CCFloat * value7 = CCFloat::create(100);
    CCFloat * effecttime7 = CCFloat::create(3000);
    
    dict7->setObject(effectobject7, "effobj");
    dict7->setObject(effectproperty7, "effproperty");
    dict7->setObject(value7, "value");
    dict7->setObject(effecttime7, "effecttime");
    
    
    CCDictionary * dict8 = CCDictionary::create();
    
    CCInteger * effectobject8 = CCInteger::create(0);
    CCInteger * effectproperty8 = CCInteger::create(4);
    CCFloat * value8 = CCFloat::create(0);
    CCFloat * effecttime8 = CCFloat::create(100);
    
    dict8->setObject(effectobject8, "effobj");
    dict8->setObject(effectproperty8, "effproperty");
    dict8->setObject(value8, "value");
    dict8->setObject(effecttime8, "effecttime");
    
    
    
    
    effectdict->setObject(dict1, 0);
    effectdict->setObject(dict2, 1);
    effectdict->setObject(dict3, 2);
    effectdict->setObject(dict4, 3);
    effectdict->setObject(dict5, 4);
    effectdict->setObject(dict6, 5);
    effectdict->setObject(dict7, 6);
    effectdict->setObject(dict8, 7);
    
    
    effectdict->retain();
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
            return i;
            //return 0;
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
Block * BlockManager::createBlock(int type)
{
    int bt;
    bt = type;
    //根据获取的障碍类型获得对应的数值参数
    Block * bl = Block::create();
    bl->retain();
    //    for (int i = 0; i < BlockCreateNumber[bt]; i++) {
    //        //根据获取的障碍类型获得对应的数值参数
    //        Block * bl = Block::create();
    
    CCDictionary * blockproer = (CCDictionary *)dict->objectForKey(bt);
    //CCDictionary * blockproer = (CCDictionary *)dict->objectForKey(0);
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
    if (bl->getWidth() == 2) {
        int ix = rand() % 4;
        int iy = rand() % 2;
        bl->setW_index(ix);
        bl->setH_index(iy);
    }
    else
    {
        int ix = rand() % 5;
        int iy = rand() % 4;
        bl->setW_index(ix);
        bl->setH_index(iy);
    }
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
    int bk = getCreateBlockType();
    int crnm =BlockCreateNumber[bk];
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
        Block * block = createBlock(bk);
        Sprite * blockactor =dynamic_cast<Sprite*>(block->getActor());
        blockactor->setAnchorPoint(ccp(0,0));
        //blockactor->setScale(0.75, 1.0);
        blockactor->setPosition(origin.x + 20 + (block->getW_index() + (int)track->getTrackState()) * track->getCircuitWidth(), origin.y + block->getH_index() * track->getCircuitWidth() * 0.5 + visibleSize.height);
        render_node->addChild(block);
        blocklist->addObject(block);
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
//                        if (blockactor->getPositionX() + blockactor->getContentSize().width <= 0) {
//                            block->setIsActive(false);
//                        }
                        if (blockactor->getPositionX() <= origin.x) {
                            block->setMoveLeftRightEnable(false);
                        }
                        break;
                    case 1://右
                        blockactor->setPositionX(blockactor->getPositionX() + block->getMoveLeftRight().speed);
//                        if (blockactor->getPositionX()  >= visibleSize.width) {
//                            block->setIsActive(false);
//                        }
                        if (blockactor->getPositionX() + blockactor->getContentSize().width >= visibleSize.width) {
                            block->setMoveLeftRightEnable(false);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        
    }
}

void BlockManager::isCollision(Player * player)
{
    //Player * player = player;
    Ref * obj;
    CCRect rect = player->getBoundingBox();
    CCARRAY_FOREACH(blocklist, obj){
        
        Block * block = (Block *)obj;
        Sprite * blockactor =dynamic_cast<Sprite*>(block->getActor());
        //CCRect rect = player->getBoundingBox();
        CCPoint point = blockactor->getPosition();
        if (rect.containsPoint(point)) {
            CCArray * effli = block->getEffectlist();
            int count = effli->count();
            for (int i = 0; i < count; i++) {
                CCInteger * id = dynamic_cast<CCInteger*>(effli->getObjectAtIndex(i));
                
                //Effect * eobj = Effect::create();
                
                CCDictionary * effctproer = (CCDictionary *)effectdict->objectForKey(id->getValue());
                CCInteger * effectobject = effctproer->objectForKey("effobj");
                int effectobjectv = effectobject->getValue();
                
                //CCInteger * effectproperty = effctproer->objectForKey("effproperty");
                int effectproperty = dynamic_cast<CCInteger * >(effctproer->objectForKey("effproperty"))->getValue();
                
                //CCFloat * value = effctproer->objectForKey("value");
                float value = dynamic_cast<CCFloat*>(effctproer->objectForKey("value"))->getValue();
                //CCFloat * effcttime = effctproer->objectForKey("effecttime");
                float effcttime = dynamic_cast<CCFloat*>(effctproer->objectForKey("effecttime"))->getValue();
                switch (effectobjectv) {
                    case 0:
                        switch (effectproperty) {
                            case 0:
                                player->setTotalStamina(player->getTotalStamina() + value);
                                break;
                            case 1:
                                player->setScore(player->getScore() + value);
                                break;
                            case 2:
                                break;
                            case 3:
                                player->setPickUpDistance(player->getPickUpDistance() + value);
                                magnet_time = effecttime;
                            case 4:
                                block_dizzy = effecttime;
                                break;
                            default:
                                break;
                        }
                        break;
                    case 1:
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
















