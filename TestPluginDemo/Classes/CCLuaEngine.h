//
//  CCLuaEngine.h
//  TestPluginDemo
//
//  Created by 龙灵修 on 14-1-16.
//
//

#ifndef __TestPluginDemo__CCLuaEngine__
#define __TestPluginDemo__CCLuaEngine__

#include "cocos2d.h"
USING_NS_CC;
#include "lua.hpp"
#include <string>
using namespace std;

class CCLuaEngine {
    
    
public:
    
    static string getPath(){
        
        return  CCFileUtils::sharedFileUtils()->getWritablePath();
    }
    
    CCLuaEngine();
    ~CCLuaEngine();
    static CCLuaEngine* getInstance();
private:
    bool init();
    static CCLuaEngine* i;
    lua_State* m_pLuaState;
};

#endif /* defined(__TestPluginDemo__CCLuaEngine__) */
