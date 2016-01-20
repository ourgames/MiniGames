//
//  CommonUtil.hpp
//  minigame1
//
//  Created by 葛富臻 on 16/1/20.
//
//

#ifndef CommonUtil_hpp
#define CommonUtil_hpp

#include <stdio.h>
#include <string>
#include "cocos2d.h"
#include "LocalController.h"

using namespace std;

class CommonUtil
{
public:
    static std::string getPropById(std::string xmlId,std::string propName);
    static cocos2d::CCArray * split(const char* src, const char* sym);
    static std::string itos(int val);
};
#endif /* CommonUtil_hpp */
