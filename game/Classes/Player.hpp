//
//  Player.hpp
//  game
//
//  Created by 葛富臻 on 15/12/11.
//
//

#ifndef Player_hpp
#define Player_hpp


#define PLAYER_INITIAL_SPEED 4
#define PLAYER_JUMP 15
#define GRAVITY 1.3f
#define FLOATING_GRAVITY 0.4f
#define TERMINAL_VELOCITY 70
#define FLOATING_FRICTION 0.98f
#define AIR_FRICTION 0.99f

#include <stdio.h>
#include "cocos2d.h"
#include "GameSprite.hpp"

USING_NS_CC;

typedef enum
{
    kPlayerMoving,
    kPlayerFalling,
    kPlayerDying
} PlayerState;

class Player : public GameSprite{
    CCAction * _rideAnimation;
    CCAction * _floatAnimation;
    float _speed;
    int _floatingTimerMax;
    float _floatingTimer;
    int _floatingInterval;
    bool _hasFloated;
    CCSize _screenSize;
    void initPlayer(void);
public:
    Player(void);
    ~Player(void);
    
    CC_SYNTHESIZE(PlayerState, _state, State);
    CC_SYNTHESIZE(bool, _inAir, InAir);
    CC_SYNTHESIZE_READONLY(bool, _floating, Floating);
    CC_SYNTHESIZE(bool, _jumping, Jumping);
    CC_SYNTHESIZE(float, _maxSpeed, MaxSpeed);
    
    static Player * create(void);
    
    virtual void update(float dt);
    
    void setFloating(bool value);
    
    void reset(void);
    
    inline virtual void place()
    {
        this->setPositionY( _nextPosition.y );
        if (_vector.x > 0 && this->getPositionX() < _screenSize.width * 0.2f) {
            this->setPositionX(this->getPositionX() + _vector.x);
            if (this->getPositionX() > _screenSize.width * 0.2f) {
                this->setPositionX(_screenSize.width * 0.2f);
            }
        }
    }
    //
    inline int left() {
        return this->getPositionX() - _width * 0.5f;
    }
    
    //
    inline int right() {
        return this->getPositionX() + _width * 0.5f;
    }
    
    //
    inline int top() {
        return this->getPositionY() ;
    }
    
    //
    inline int bottom() {
        return this->getPositionY() - _height ;
    }
    
    //
    inline int next_left() {
        return _nextPosition.x - _width * 0.5f;
    }
    
    //
    inline int next_right() {
        return _nextPosition.x + _width * 0.5f;
    }
    
    //
    inline int next_top() {
        return _nextPosition.y ;
    }
    
    //
    inline int next_bottom() {
        return _nextPosition.y - _height;
    }
};
#endif /* Player_hpp */
