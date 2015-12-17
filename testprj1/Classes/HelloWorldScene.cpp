#include "HelloWorldScene.h"

USING_NS_CC;

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("bg.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    SpriteFrameCache * frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("sprite_sheet.plist", "sprite_sheet.png");
    auto player = Sprite::createWithSpriteFrameName("player_1.png");
    player->setPosition(origin.x + player->getContentSize().width * 0.5, visibleSize.height * 0.3);
    this->addChild(player,1);
    
    Animation * animation = Animation::create();
    SpriteFrame * frame;
    int i;
    for (i=1; i<=3; i++) {
        char szName[100] = {0};
        sprintf(szName, "player_%i.png",i);
        frame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        animation->addSpriteFrame(frame);
    }
    //animation->setDelayPerUnit(0.2f/0.3f);
    animation->setDelayPerUnit(2.8f/14.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);//使动画不断的执行
    
    auto action = Animate::create(animation);
    player->runAction(Sequence::create(action,action->reverse(),NULL));
    
    CCArray * clouds = CCArray::createWithCapacity(4);
    Sprite * cloud;
    float cloud_y;
    for (int i = 0; i < 4; i++) {
        cloud_y = i % 2 == 0 ? visibleSize.height * 0.7f : visibleSize.height * 0.8f;
        cloud = Sprite::createWithSpriteFrameName("cloud.png");
        cloud->cocos2d::Node::setPosition(ccp(visibleSize.width * 0.15f + i * visibleSize.width * 0.25f,cloud_y));
        this->addChild(cloud,1);
        clouds->addObject(cloud);
    }
    /*
    int count = clouds->count();
    for (int i = 0; i < count; i++) {
        cloud = (Sprite *) clouds->objectAtIndex(i);
        cloud->setPositionX(cloud->getPositionX()- player->getPositionX() * 0.15f);
        if (cloud->getPositionX() + cloud->boundingBox().size.width * 0.5f < 0) {
            cloud->setPositionX(visibleSize.width + cloud->boundingBox().size.width * 0.5f);
        }
    }
    */
    Sprite * terrain1 = Sprite::createWithSpriteFrameName("background.png");
    //terrain->setAnchorPoint(ccp(0,0));
    //terrain->setPosition(origin.x + terrain->getContentSize().height,origin.y + terrain->getContentSize().width);
    //terrain->setScale(0.75, 0.75);
    terrain1->setPosition(terrain1->getContentSize().width * 0.5f, terrain1->getContentSize().height * 0.5f);
    //terrain->setScale(0.75, 0.75);
    this->addChild(terrain1,0);
    
    
    Sprite * terrain2 = Sprite::createWithSpriteFrameName("background.png");
    terrain2->setPosition(visibleSize.width - terrain2->getContentSize().width * 0.5f, terrain2->getContentSize().height * 0.5f);
    this->addChild(terrain2,0);
    
    //auto flipxAction = FlipX::create(true);
    //auto bk_moveTo = MoveTo::create(1.4f, Point(visibleSize.width - terrain->getContentSize().width * 0.5f,terrain->getContentSize().height * 0.5f));
    auto bk_moveTo1 = MoveTo::create(1.4f, Point(visibleSize.width - terrain1->getContentSize().width * 0.5f,terrain1->getContentSize().height * 0.5f));
    auto bk_moveTo2 = MoveTo::create(1.4f, Point(terrain2->getContentSize().width * 0.5f,terrain2->getContentSize().height * 0.5f));
    //auto bk_action = Sequence::create(moveTo,flipxAction,moveTo->reverse(), NULL);
    
    //terrain1->runAction(bk_moveTo1);
    //terrain2->runAction(bk_moveTo2);
    
    auto pl_moveTo = MoveTo::create(1.5f, Point(visibleSize.width * 0.5,visibleSize.height * 0.3));
    player->runAction(pl_moveTo);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
