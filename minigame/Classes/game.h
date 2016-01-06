//
//  game.h
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#ifndef game_h
#define game_h

typedef enum {
    player,
    other
} EffectObject;

typedef enum {
    hp,
    score,
    speed,
    distance,
    movement
} EffectProperty;

typedef struct {
    int type;//上下，左右，
    bool enable;//不可移动
    int direction;
    float speed;
} Movement;

typedef enum {
    NormalBlock = 0,
    BigBlock = 1,
    DizzyBlock = 2,
    LeftBlock = 3,
    RightBlock = 4,
    TrackBlock = 5,
    HighSpeedBlock = 6
} BlockType;

typedef enum{
    Coin,
    Invincible,
    HP,
    Magnet
} ItemType;

typedef  enum {
    Left = 0,
    Middle = 1,
    Right = 2
} TrackState;

//class Movement :public cocos2d::Ref
//{
//    CC_SYNTHESIZE(int, type, Type);
//    CC_SYNTHESIZE(bool, enable, Enable);
//    CC_SYNTHESIZE(int, direction, Direction);
//    CC_SYNTHESIZE(float, speed, Speed);
//public:
//    Movement(int type,bool enable,int direction,float speed):type(type),enable(enable),direction(direction),speed(speed)
//    {
//    }
//    Movement * create(int type,bool enable,int direction,float speed)
//    {
//        Movement * movement1 = new Movement(type,enable,direction,speed);
//        return movement1;
//    }
//    ~Movement(){};
//};

static int BlockNum = 7;
static int ItemNum = 4;
static int EffectNumber = 10;
#endif /* game_h */
