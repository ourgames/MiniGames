//
//  GameLayer.h
//  game
//
//  Created by 葛富臻 on 15/12/11.
//
//

#ifndef GameLayer_h
#define GameLayer_h

USING_NS_CC;

typedef enum{
    kGameIntro,
    kGamePlay,
    kGameOver,
    kGameTutorial,//
    kGameTutorialJump,//
    kGameTutorialFloat,//
    kGameTutorialDrop//
} GameState;

class GameLayer : public cocos2d::CCLayer
{
    Terrain * _terrain;
    Player * _player;
    CCLabelBMFont * _scoreDisplay;
    
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
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);
    
    void update (float dt);
    
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    void showTutorial (CCObject* pSender);
    void startGame (CCObject* pSender);
};

#endif /* GameLayer_h */
