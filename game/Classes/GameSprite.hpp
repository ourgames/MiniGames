//
//  GameSprite.hpp
//  game
//
//  Created by 葛富臻 on 15/12/11.
//
//

#ifndef GameSprite_hpp
#define GameSprite_hpp

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

enum {
    kBackgroud,
    kMiddlegroud,
    kForegroud
};

enum {
    kSpritePlayer,
    kSpriteTerrain,
    kSpriteBlock,
    kSpriteChimney,
    kSpritePuff
};

class GameSprite : public CCSprite {
protected:
    CCSize _screenSize;
public:
    CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
    CC_SYNTHESIZE(float, _width, Width);
    CC_SYNTHESIZE(float, _height, Height);
    CC_SYNTHESIZE(CCPoint, _vector, Vector);
    
    GameSprite(void);
    ~GameSprite(void);
    
    inline virtual void place (){ this->cocos2d::Node::setPosition(_nextPosition);};
    
    inline virtual float radius()
    {
        return _width*0.5f;
    }
    
    inline void setSize()
    {
        _width = this->boundingBox().size.width;
        _height = this->boundingBox().size.height;
    }
};
#endif /* GameSprite_hpp */
