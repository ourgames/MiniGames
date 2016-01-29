//
//  CommonUtil.cpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/20.
//
//

#include "CommonUtil.hpp"


std::string CommonUtil::getPropById(std::string xmlId, std::string propName)
{
    auto retDict = LocalController::shared()->DBXMLManager()->getObjectByKey(xmlId);
    if (!retDict) {
        return string("");
    }
    auto ret = retDict->valueForKey(propName);
    if (!ret->getCString()) {
        return string("");
    }
    return string(ret->getCString());
    
}

CCArray* CommonUtil::split(const char* src, const char* sym)
{
    CCArray * ret = CCArray::create();
    
    std::string s = src;
    
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = s.find(sym, nbegin);
        if(nend == -1)
            ret->addObject(CCString::create(s.substr(nbegin, s.length()-nbegin)));
        else
            ret->addObject(CCString::create(s.substr(nbegin, nend-nbegin)));
        nbegin = nend + strlen(sym);
    }
    //ret->retain();
    //ret->autorelease();
    return ret;
}

std::string CommonUtil::itos(int val)
{
    std::string res;
    stringstream buff;
    buff << val;
    buff >> res;
    return res;
}