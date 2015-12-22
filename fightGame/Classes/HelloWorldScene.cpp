#include "HelloWorldScene.h"

USING_NS_CC;

enum
{
    kTagSprite = 1,
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("yejing.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    createGameScreen();
   
    this->schedule(schedule_selector(HelloWorld::update),0.1);
    
    this->setTouchEnabled(true);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HelloWorld::createGameScreen()
{
    bg = CCArray::createWithCapacity(3);
    Sprite * _bg;
    bg->retain();
    for (int i = 0; i < 3; i++) {
        _bg = Sprite::create("yejing.jpg");
        _bg->setAnchorPoint(ccp(0,0));
        _bg->setPosition(0, i * _bg->getContentSize().height - 1);
        this->addChild(_bg,0);
        bg->addObject(_bg);
    }
    
    player = Sprite::create("daxia.png");
    player->setScale(0.25, 0.25);
    player->setPosition(visibleSize.width * 0.5, player->getContentSize().height * 0.25 * 0.5);
    //player->setPosition(visibleSize.width * 0.5, 0);
    this->addChild(player,1,kTagSprite);
    //this->schedule(schedule_selector(HelloWorld::update),0.1);
    
}

void HelloWorld::onExit()
{
    bg->release();
}

void HelloWorld::update(float dt)
{
    if (player->getPositionX() > 0) {
        Sprite * _bg;
        int _count = bg->count();
        for (int i = 0; i < _count; i++) {
            _bg = (Sprite * )bg->objectAtIndex(i);
            _bg->setPositionY(_bg->getPositionY() - player->getPositionY() * 0.15f);
            if (_bg->getPositionY() + _bg->boundingBox().size.height < 0) {
                Sprite * next_bg = (Sprite * )bg->objectAtIndex((i + 2) % 3);
                _bg->setPositionY(next_bg->getPositionY() + next_bg->getContentSize().height - 80);
            }
        }
    }
    
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
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

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
