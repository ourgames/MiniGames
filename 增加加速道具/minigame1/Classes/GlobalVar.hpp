//
//  GlobalVar.hpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/20.
//
//

#ifndef GlobalVar_hpp
#define GlobalVar_hpp

#include <stdio.h>
//block种类
#define BLOCKTYPENUM 7
//item种类
#define ITEMTYPENUM 4
//id基数
#define BLOCKIDBASE 1000
#define ITEMIDBASE 2000
#define EFFECTIDBASE 3000
//block生成距离
#define BLOCKCREATEDISTANCE 200
#define BLOCKTIME 1000
#define BLOCKREDUCE 50
//赛道速度，数量和宽度
#define COURCESPEED 50
#define TRACKNUM 5
#define TRACKWIDTH 80
//数组尺寸大小
#define MAXSIZE 50
#define BLOCKEFFECTLISTSIZE 10
#define ITEMEFFECTLISTSIZE 10
//player id
#define PLAYERID 4000
//item生成距离
#define ITEMDISTANCE 600
#define ITEMBLOCKDISTANCE 200

static float BlockDistance = 400;
static int BlockItemChance[2] = {60,40};
class GlobalVar
{
    
};
#endif /* GlobalVar_hpp */
