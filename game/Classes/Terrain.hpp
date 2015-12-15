//
//  Terrain.hpp
//  game
//
//  Created by 葛富臻 on 15/12/14.
//
//

#ifndef Terrain_hpp
#define Terrain_hpp

#define TILE_H_SIZE 6
#define TILE_W_SIZE 8

#include <stdio.h>
#include "cocos2d.h"
#include "Block.hpp"
#include "Player.hpp"

USING_NS_CC;
using namespace std;

class GameTerrain : public CCSprite {
    
    CCArray * _blockPool;
    int _blockPoolIndex;
    
    CCArray * _blocks;
    int _lastBlockHeight;
    int _lastBlockWidth;
    int _minTerrainWidth;
    
    bool _showGap;
    CCSize _screenSize;
    
    int _currentPatternIndex;
    int _currentPatternCnt;
    int _currentWidthIndex;
    int _currentHeightIndex;
    int _currentTypeIndex;
    
    int _increaseGapInterval;
    float _increaseGapTimer;
    int _gapSize;
    
    void initTerrain (void);
    void addBlocks(int currentWidth);
    
    void distributeBlocks();
    void initBlock(Block * block);
    
    inline float getWidth () {
        
        int count = _blocks->count();
        int width = 0;
        Block * block;
        for (int i = 0; i < count; i++) {
            block = (Block *) _blocks->objectAtIndex(i);
            width += block->getWidth();
        }
        return width;
    }
    
    
public:
    
    GameTerrain(void);
    ~GameTerrain(void);
    
    CC_SYNTHESIZE(bool, _startTerrain, StartTerrain);
    
    static GameTerrain * create();
    
    void activateChimneysAt (Player * player);
    void checkCollision (Player * player);
    
    void move (float xMove);
    void reset (void);
    
    
};
#endif /* Terrain_hpp */
