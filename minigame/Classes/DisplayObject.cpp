//
//  Effect.cpp
//  minigame
//
//  Created by 葛富臻 on 16/1/4.
//
//

#include "DisplayObject.hpp"



//BaseDisplayObject::BaseDisplayObject()
//{
//    
//}

void BaseDisplayObject::addAttribute(IAttribute * pAttribute)
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

void BaseDisplayObject::addEffect(IEffect * pEffect)
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