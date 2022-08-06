// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "api/api.h"
#include "game.h"
#include "script.h"
#include "utils.h"

#include "tables/scripts.h"

lua_State* NewLuaState(void) {
    lua_State* l = luaL_newstate();
    if (l == NULL) {
        RuntimeError("cannot create lua state: not enough memory");
    }
    APILoadLibs(l);
    return l;
}

void UpdateAPIConsts(void) {
    lua_pushstring(gGame.lua_state, GL2String(gGame.lang));
    lua_setglobal(gGame.lua_state, "GAME_LANG");
}

void LuaReport(lua_State* L, int status) {
    if (status != LUA_OK) {
        const char* msg = lua_tostring(L, -1);
        luaL_traceback(L, L, msg, -1);
        RuntimeError(lua_tostring(L, -1));
    }
}

void RunScript(int idx) {
    if (idx < 0 || idx >= ARR_LEN(SCRIPT_TABLE)) {
        RuntimeError(TextFormat("cannot run script %d (index out of range)", idx));
    }
    LuaReport(gGame.lua_state, luaL_dostring(gGame.lua_state, SCRIPT_TABLE[idx].buf));
}
