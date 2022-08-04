// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "api/api.h"
#include "game.h"
#include "scripts.h"
#include "utils.h"

lua_State* NewLuaState(void) {
    lua_State* l = luaL_newstate();
    if (l == NULL) {
        RuntimeError("cannot create lua state: not enough memory");
    }
    luaL_openlibs(l);
    APILoadLibs(l);
    return l;
}

void UpdateAPIConsts(void) {
    lua_pushstring(gGame.lua_state, GL2String(gGame.lang));
    lua_setglobal(gGame.lua_state, "GAME_LANG");
}

void RunScript(char* sc) {
    if (luaL_dostring(gGame.lua_state, sc) != LUA_OK) {
        //
    }
}
