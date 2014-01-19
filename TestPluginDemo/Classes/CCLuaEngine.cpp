//
//  CCLuaEngine.cpp
//  TestPluginDemo
//
//  Created by 龙灵修 on 14-1-16.
//
//

#include "CCLuaEngine.h"

#include <string>

/////////////////注意要按照这个CPP形式编译C否者报错/////////////////////////////////
#if __cplusplus
extern "C" {
#endif
#include "lsqlite3/lsqlite3.h"
    
    
    
    static luaL_Reg luax_my_libs[] = {
        
        { "lsqlite3", luaopen_lsqlite3},
        { NULL, NULL }
        
        
        
    };
#if __cplusplus
}
#endif

//////////////////////////////////////////////////
CCLuaEngine::CCLuaEngine(){
    
    
}

CCLuaEngine::~CCLuaEngine(){
    
    if ( m_pLuaState) {
        lua_close( m_pLuaState);
        m_pLuaState = NULL;
    }
    
}

static int l_getPath( lua_State* L ){
    
    CCLOG("调用函数");
    
    lua_pushstring( L,  CCFileUtils::sharedFileUtils()->getWritablePath().c_str());

    return 1;
}


bool CCLuaEngine::init(){
    
    m_pLuaState = luaL_newstate();
    luaL_openlibs( m_pLuaState );
    
    
    luaL_Reg* lib = luax_my_libs;
    // 调用package.preload函数来对我们要引入的插件进行一个预加载
    lua_getglobal(m_pLuaState, "package");
    lua_getfield(m_pLuaState, -1, "preload");
    
    for (; lib->func; lib++ ) {
        lua_pushcfunction(m_pLuaState, lib->func);
        lua_setfield(m_pLuaState, -2, lib->name);
        
    }
    lua_pop( m_pLuaState, 2);
    
    lua_pushcfunction(m_pLuaState,  l_getPath);
    lua_setglobal( m_pLuaState, "getPath");
    
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename( "my.lua");
    
    luaL_dofile( m_pLuaState, path.c_str());
    lua_pcall(m_pLuaState, 0, 0, -1);
    
    
    
    return true;
}


CCLuaEngine* CCLuaEngine::i = NULL;
CCLuaEngine* CCLuaEngine::getInstance(){
    
    if ( !i ) {
        i = new CCLuaEngine;
        i->init();
    }
    return i ;
}


