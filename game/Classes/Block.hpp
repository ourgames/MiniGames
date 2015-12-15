//
//  Block.hpp
//  game
//
//  Created by 葛富臻 on 15/12/14.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameSprite.hpp"

USING_NS_CC;


enum {
    kWallTile,
    kRoofTile,//
    kChimney //
};

enum  {
    kBlockGap,//
    kBlock1,
    kBlock2,
    kBlock3,
    kBlock4
    
};

//
class Block : public GameSprite {
    
    //
    CCSize _screenSize;
    
    int _tileWidth;
    int _tileHeight;
    int _puffIndex;
    
    CCSpriteFrame * _tile1;
    CCSpriteFrame * _tile2;
    CCSpriteFrame * _tile3;
    CCSpriteFrame * _tile4;
    
    CCSpriteFrame * _roof1;//
    CCSpriteFrame * _roof2;//
    
    CCArray * _wallTiles;
    CCArray * _roofTiles;
    
    CCAction * _puffSpawn;
    CCAction * _puffMove;
    CCAction * _puffFade;
    CCAction * _puffScale;
    CCAction * _puffAnimation;
    
    void initBlock(void);
    void createPuff(void);
public:
    
    CC_SYNTHESIZE(int, _type, Type);
    
    //
    CC_SYNTHESIZE_READONLY(bool, _puffing, Puffing);
    
    //
    CC_SYNTHESIZE(CCArray *, _chimneys, Chimneys);
    
    Block();
    ~Block();
    
    static Block * create();
    void setupBlock (int width, int height, int type);
    void setPuffing (bool value);
    void hidePuffs();
    
    inline virtual int left() {
        return this->getPositionX();
    }
    
    inline virtual int right() {
        return this->getPositionX() + _width;
    }
    
    inline virtual int top() {
        return this->getHeight();
    }
    
    inline virtual int bottom() {
        return 0;
    }
    
    
};
#endif /* Block_hpp */
