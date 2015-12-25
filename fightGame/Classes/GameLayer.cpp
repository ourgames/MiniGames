//
//  GameLayer.cpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/23.
//
//

#include "GameLayer.hpp"

USING_NS_CC;

enum
{
    kTagSprite = 1,
    kActionLayer = 2,
    kTagSprite2 = 3,
};

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    delay = 1.5;
    totletime = 0;
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameLayer::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto closeItem2 = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameLayer::menuCloseCallback2, this));
    
    closeItem2->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * 3 / 2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto closeItem3 = MenuItemImage::create(
                                            "CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(GameLayer::menuCloseCallback3, this));
    
    closeItem3->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * 5 / 2,origin.y + closeItem->getContentSize().height/2));
    
//    auto pausetab = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameLayer::menuCloseCallback2, this));
//    pausetab->setPosition(Vec2(closeItem->getPositionX() - closeItem->getContentSize().width/2 - pausetab->getContentSize().width/2,
//                               origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem,pausetab, NULL);
    auto menu = Menu::create(closeItem, closeItem2, closeItem3, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    createGameScreen();
    
    //this->schedule(schedule_selector(HelloWorld::update),0.1);
    //this->schedule(schedule_selector(HelloWorld::update));
    this->scheduleUpdate();
    
    this->setTouchEnabled(true);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GameLayer::createGameScreen()
{
    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
    
    bg = CCArray::createWithCapacity(4);
    Sprite * _bg;
    bg->retain();
    for (int i = 0; i < 4; i++) {
        _bg = Sprite::create("yejing.jpg");
        _bg->setAnchorPoint(ccp(0,0));
       // _bg->setPosition(0, i * _bg->getContentSize().height - 1);
        _bg->setPosition(origin.x,origin.y + i * _bg->getContentSize().height - 1);
        this->addChild(_bg,-100);
        bg->addObject(_bg);
    }
    
//    auto layer = cocos2d::Layer::create();
//    this->addChild(layer,100,kActionLayer);
//    
    player = Sprite::create("daxia.png");
    player->setScale(0.25, 0.25);
    player->setPosition(origin.x + visibleSize.width * 0.5,origin.y + player->getContentSize().height * 0.25 * 0.5);
    this->addChild(player,1,kTagSprite);
    
    auto player2 = Sprite::create("xiaobai.jpg");
    player2->setScale(0.5, 0.5);
    player2->setPosition(origin.x + visibleSize.width * 0.5,origin.y + visibleSize.height * 0.5);
    this->addChild(player2,1,kTagSprite2);
    
//    layer->addChild(player,10,kTagSprite);
//    createObstacle(10,layer);
}

void GameLayer::createObstacle(int num,cocos2d::Node * render_node)
{
    //clouds = CCArray::createWithCapacity(35);
    //clouds->retain();
    
    for (int i = 0; i < num; i++) {
        int rand_w = rand() % 5;
        int rand_h = rand() % 7;
        
        Sprite * _cloud = Sprite::createWithSpriteFrameName("cloud.png");
        _cloud->setAnchorPoint(ccp(0,0));
        _cloud->setPosition(origin.x + rand_w * 128,origin.y + rand_h * 128 + 64 + visibleSize.height);
        
        float distance = origin.y + rand_h * 128 + 64 + visibleSize.height + _cloud->getContentSize().height;
        float time = distance / 30;
        auto obstacle_moveTo = MoveTo::create(time, Point(origin.x + rand_w * 128,origin.y - _cloud->getContentSize().height));
        _cloud->runAction(obstacle_moveTo);
        
        render_node->addChild(_cloud,10);
        
        //clouds->addObject(_cloud);
        //w->addObject(rand_w);
        
    }
    
}

bool GameLayer::isCollasion()
{
    auto s1 = getChildByTag(kTagSprite);
    auto s2 = getChildByTag(kTagSprite2);
    CCRect rect = s1->getBoundingBox();
    CCPoint point = s2->getPosition();
    return rect.containsPoint(point);
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();
}

void GameLayer::onExit()
{
    bg->release();
    
    //clouds->release();
    
    CCLayer::onExit();
}

void GameLayer::update(float dt)
{
    totletime += dt;
    if (totletime >= delay) {
        int number = rand() % 5;
        createObstacle(number, this);
        totletime = 0;
    }
    if (player->getPositionX() > 0) {
        Sprite * _bg;
        //bg->retain();
        int _count = bg->count();
        for (int i = 0; i < _count; i++) {
            _bg = (Sprite * )bg->objectAtIndex(i);
            //_bg->setPositionY(_bg->getPositionY() - player->getPositionY() * 0.15f);
            _bg->setPositionY(_bg->getPositionY() - 20);
            if (_bg->getPositionY() + _bg->boundingBox().size.height < 0) {
                Sprite * next_bg = (Sprite * )bg->objectAtIndex((i + 2) % 3);
                _bg->setPositionY(next_bg->getPositionY() + next_bg->getContentSize().height - 80);
            }
        }
        //bg->release();
        /*
        auto s = getChildByTag(kActionLayer);
        s->setPositionY(s->getPositionY() - 3);
        if (s->getPositionY() + s->boundingBox().size.height < 0) {
            ;
        }
        */
//        Sprite * _obstacle;
//        ///clouds->retain();
//        int _obstaclecount = clouds->count();
//        for (int i = 0; i < _obstaclecount; i++) {
//            _obstacle = (Sprite * )clouds->objectAtIndex(i);
//            _obstacle->setPositionY(_obstacle->getPositionY() - 20);
//            if (_obstacle->getPositionY() + _obstacle->boundingBox().size.height < 0) {
//                clouds->removeObjectAtIndex(i);
//            }
//        }
        //clouds->release();
        if (isCollasion()) {
            auto s1 = getChildByTag(kTagSprite);
            auto s2 = getChildByTag(kTagSprite2);
            s2->setVisible(false);
        }
    }
    else
    {
        Sprite * _bg;
        int _count = bg->count();
        for (int i = 0; i < _count; i++) {
            _bg = (Sprite * )bg->objectAtIndex(i);
            _bg->stopAllActions();
        }
    }
    
    
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto location = touch->getLocation();
    
    auto s = getChildByTag(kTagSprite);
    //s->stopAllActions();
    s->runAction(MoveTo::create(1, Vec2(location.x,location.y)));
    float o = location.x - s->getPosition().x;
    float a = location.y - s->getPosition().y;
    float at = (float) CC_RADIANS_TO_DEGREES(atanf(o/a));
    
    if (a < 0) {
        if (o < 0) {
            at = 180 + fabs(at);
        }
        else
            at = 180 - fabs(at);
    }
    //s->runAction(RotateTo::create(1, at));
}

void GameLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void GameLayer::menuCloseCallback2(Ref* pSender)
{
    Director::getInstance()->pause();
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}
void GameLayer::menuCloseCallback3(Ref* pSender)
{
    Director::getInstance()->resume();
    
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    exit(0);
    //#endif
}






















/*
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
USING_NS_CC;
using namespace ui;

class LayerMultiplexDemo : public Scene
{
public:
    CREATE_FUNC(LayerMultiplexDemo);
    virtual bool init();
};

class BaseLayer : public Layer
{
public:
    CREATE_FUNC(BaseLayer);
    virtual bool init();
    Text* text;
    Size winSize;
};

class MainLayer : public BaseLayer
{
public:
    CREATE_FUNC(MainLayer);
    virtual bool init();
    
    void menuCallback1(Ref* sender);
    void menuCallback2(Ref* sender);
    void menuCallback3(Ref* sender);
};

class Layer1 : public BaseLayer
{
public:
    CREATE_FUNC(Layer1);
    virtual bool init();
    void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

class Layer2 : public BaseLayer
{
public:
    CREATE_FUNC(Layer2);
    virtual bool init();
    void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

class Layer3 : public BaseLayer
{
public:
    CREATE_FUNC(Layer3);
    virtual bool init();
    void touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

#include "LayerMultiplexDemo.h"
bool LayerMultiplexDemo::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!Scene::init());
        
        MenuItemFont::setFontSize(20);
        
        auto layer  = MainLayer::create();
        auto layer1 = Layer1::create();
        auto layer2 = Layer2::create();
        auto layer3 = Layer3::create();
        
        auto layerMultiplex = LayerMultiplex::create(layer,layer1, layer2, layer3, nullptr);
        addChild(layerMultiplex, 0);
        
        bRet = true;
    }while(0);
    return bRet;
}

bool BaseLayer::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!Layer::init());
        winSize = Director::getInstance()->getWinSize();
        
        text = Text::create();
        text->setFontSize(40);
        text->setPosition(Vec2(winSize.width/2,winSize.height - 100));
        addChild(text);
        
        bRet = true;
    }while(0);
    return bRet;
}

bool MainLayer::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!BaseLayer::init());
        text->setString("Hello! This is MainLayer!");
        
        auto label1 = Label::createWithBMFont("bitmapFontTest3.fnt", "Layer 1");
        auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(MainLayer::menuCallback1, this));
        
        auto label2 = Label::createWithBMFont("bitmapFontTest3.fnt", "Layer 2");
        auto item2 = MenuItemLabel::create(label2, CC_CALLBACK_1(MainLayer::menuCallback2, this));
        
        auto label3 = Label::createWithBMFont("bitmapFontTest3.fnt", "Layer 3");
        auto item3 = MenuItemLabel::create(label3, CC_CALLBACK_1(MainLayer::menuCallback3, this));
        
        auto menu = Menu::create(item1,item2,item3,nullptr);
        menu->alignItemsVertically();
        addChild(menu);
        menu->setPosition(Vec2(winSize.width/2,winSize.height/2));
        
        bRet = true;
    }while(0);
    return bRet;
}

void MainLayer::menuCallback1(cocos2d::Ref *sender)
{
    static_cast<layermultiplex*>(_parent)->switchTo(1);
}

void MainLayer::menuCallback2(cocos2d::Ref *sender)
{
    static_cast<layermultiplex*>(_parent)->switchTo(2);
}
void MainLayer::menuCallback3(cocos2d::Ref *sender)
{
    static_cast<layermultiplex*>(_parent)->switchTo(3);
}


bool Layer1::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!BaseLayer::init());
        
        text->setString("Hello! This is Layer1");
        
        auto layout = Layout::create();
        layout->setContentSize(Size(300,300));
        layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        layout->setBackGroundColor(Color3B::GRAY);
        layout->ignoreAnchorPointForPosition(false);
        layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        layout->setPosition(Vec2(winSize.width/2,winSize.height/2));
        addChild(layout);
        auto button = Button::create("btn-about-normal.png","btn-about-selected.png");
        button->setPosition(Vec2(layout->getContentSize().width/2,layout->getContentSize().height/2));
        layout->addChild(button);
        button->addTouchEventListener(CC_CALLBACK_2(Layer1::touchEvent, this));
        
        bRet = true;
    }while(0);
    return bRet;
}
void Layer1::touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    static_cast<layermultiplex*>(_parent)->switchTo(0);
}


bool Layer2::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!BaseLayer::init());
        text->setString("Hello! This is Layer2");
        
        auto layout = Layout::create();
        layout->setContentSize(Size(300,300));
        layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        layout->setBackGroundColor(Color3B::GRAY);
        layout->ignoreAnchorPointForPosition(false);
        layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        layout->setPosition(Vec2(winSize.width/2,winSize.height/2));
        addChild(layout);
        auto button = Button::create("btn-about-normal.png","btn-about-selected.png");
        button->setPosition(Vec2(layout->getContentSize().width/2,layout->getContentSize().height/2));
        layout->addChild(button);
        button->addTouchEventListener(CC_CALLBACK_2(Layer2::touchEvent, this));
        
        bRet = true;
    }while(0);
    return bRet;
}
void Layer2::touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    static_cast<layermultiplex*>(_parent)->switchTo(0);
}


bool Layer3::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!BaseLayer::init());
        text->setString("Hello! This is Layer3");
        
        auto layout = Layout::create();
        layout->setContentSize(Size(300,300));
        layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
        layout->setBackGroundColor(Color3B::GRAY);
        layout->ignoreAnchorPointForPosition(false);
        layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        layout->setPosition(Vec2(winSize.width/2,winSize.height/2));
        addChild(layout);
        auto button = Button::create("btn-about-normal.png","btn-about-selected.png");
        button->setPosition(Vec2(layout->getContentSize().width/2,layout->getContentSize().height/2));
        layout->addChild(button);
        button->addTouchEventListener(CC_CALLBACK_2(Layer3::touchEvent, this));
        
        bRet = true;
    }while(0);
    return bRet;
}
void Layer3::touchEvent(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    static_cast<layermultiplex*>(_parent)->switchTo(0);
}</layermultiplex*></layermultiplex*></layermultiplex*></layermultiplex*></layermultiplex*></layermultiplex*>
 
 */
