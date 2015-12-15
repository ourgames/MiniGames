//
//  GameLayer.h
//  game
//
//  Created by 葛富臻 on 15/12/11.
//
//

#ifndef GameLayer_h
#define GameLayer_h

#include "cocos2d.h"
#include "Terrain.hpp"
#include "Player.hpp"

USING_NS_CC;

typedef enum{
    kGameIntro,//游戏介绍
    kGamePlay,//开始游戏
    kGameOver,
    kGameTutorial,//
    kGameTutorialJump,//
    kGameTutorialFloat,//
    kGameTutorialDrop//
} GameState;

class GameLayer : public cocos2d::Layer
{
    GameTerrain * _terrain;
    Player * _player;
    LabelBMFont * _scoreDisplay;
    
    CCSprite * _intro;
    CCSprite * _tryAgain;
    CCSprite * _background;
    CCSprite * _foreground;
    CCSprite * _hat;
    CCSprite * _jam;
    CCAction * _jamAnimate;
    CCAction * _jamMove;
    
    CCArray * _clouds;
    CCSpriteBatchNode * _gameBatchNode;
    CCLabelTTF * _tutorialLabel;
    CCMenu* _mainMenu;
    
    CCSize _screenSize;
    
    GameState _state;
    bool _running;
    float _score;
    int _speedIncreaseInterval;
    float _speedIncreaseTimer;
    void createGameScreen();
    void resetGame();
public:
    ~GameLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);
    
    void update (float dt);
    
    virtual void onTouchesBegan(CCSet* pTouches, CCEvent* event);
    virtual void onTouchesEnded(CCSet* pTouches, CCEvent* event);
    void showTutorial (CCObject* pSender);
    void startGame (CCObject* pSender);
};

#endif /* GameLayer_h */
