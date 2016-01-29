//
//  Track.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/29.
//
//

#include "Track.hpp"
#include "GlobalVar.hpp"

Track::Track()
{
    if (mAttributeList.empty()) {
        mAttributeList.reserve(MAXSIZE);
    }
    if (mAttributeKeyList.empty()) {
        mAttributeKeyList.reserve(MAXSIZE);
    }
}

Track::~Track()
{
    mAttributeList.clear();
    mAttributeKeyList.clear();
}

Track * Track::create()
{
    Track * track = new (std::nothrow) Track();
    if (track && track->init()) {
        track->autorelease();
        return track;
    }
    CC_SAFE_DELETE(track);
    return nullptr;
}

bool Track::init()
{
    bool result;
    
    IAttribute * pXSpeedAttribute = Attribute::create(AttributeType::SPEED_X, 0);
    IAttribute * pYSpeedAttribute = Attribute::create(AttributeType::SPEED_Y, 0);
    
    if (pXSpeedAttribute && pYSpeedAttribute ) {
        addAttribute(pXSpeedAttribute);
        addAttribute(pYSpeedAttribute);
        result = true;
    }
    else result = false;
    
    return result;
}

void Track::addAttribute(IAttribute * pAttribute)
{
    if(pAttribute)
    {
        int key = pAttribute->getKey();
        if(mAttributeList.at(key) == nullptr)
        {
            mAttributeList.insert(key, pAttribute);
            pAttribute->setDisplayObject(this);
            mAttributeKeyList.push_back(key);
        }
        
    }
}

void Track::addEffect(IEffect * pEffect)
{
    if(!pEffect)
        return;
    int key = pEffect->getAttributeKey();
    IAttribute * pAttribute = mAttributeList.at(key);
    if(pAttribute)
    {
        pAttribute->addEffect(pEffect);
    }
}

void Track::update(float dt)
{
    updatePosition(dt);
    updateAttribute(dt);
}

 void Track::updatePosition(float dt)
{
    float xSpeed = getAttributeValueByKey(AttributeType::SPEED_X);
    float ySpeed = getAttributeValueByKey(AttributeType::SPEED_Y);
    this->setPositionX(this->getPositionX() + dt * xSpeed);
    this->setPositionY(this->getPositionY() + dt * ySpeed);
    
}
 void Track::updateAttribute(float dt)
{
    for(auto iter = mAttributeKeyList.begin(); iter != mAttributeKeyList.end(); ++iter)
    {
        int key = *(iter);
        IAttribute * pAttribute = mAttributeList.at(key);
        if(pAttribute)
        {
            pAttribute->update(dt);
        }
    }
}
