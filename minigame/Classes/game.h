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
    NormalBlock,
    BigBlock,
    DizzyBlock,
    LeftBlock,
    RightBlock,
    TrackBlock,
    HighSpeedBlock
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

#endif /* game_h */
