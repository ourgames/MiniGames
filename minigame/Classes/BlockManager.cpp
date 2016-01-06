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
    CCInteger *createnum1 = CCInteger::create(4);
    
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


Block * BlockManager::createBlock()
{
    int bt;
    int randNum = rand() % 100 + 1;
    int tempNum = 1;
    for (int i = 0; i < BlockNum; i++) {
        if (randNum >= tempNum && randNum < tempNum + blockcreatechance[i]) {
            bt = i;
            break;
        }
        else
            tempNum += blockcreatechance[i];
    }
    //根据获取的障碍类型获得对应的数值参数
    Block * bl = Block::create();
    bl->retain();
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
    int ix = rand() % 4;
    int iy = rand() % 5;
    bl->setW_index(ix);
    bl->setH_index(iy);
    //设置运动
    MoveMent * objmv = dynamic_cast<MoveMent *>(blockproer->objectForKey("movementud"));
    Movement mvstrut= {objmv->getType(),objmv->getEnable(),objmv->getDirection(),objmv->getSpeed()};
    bl->setMoveUpDown(mvstrut);
    
    MoveMent * objmv2 = dynamic_cast<MoveMent *>(blockproer->objectForKey("movementlr"));
    Movement mvstrut2= {objmv2->getType(),objmv2->getEnable(),objmv2->getDirection(),objmv2->getSpeed()};
    bl->setMoveUpDown(mvstrut2);
    
    return bl;
    //
    //
}
BlockManager::~BlockManager()
{
    delete [] blockcreatechance;
    dict->release();
}
















