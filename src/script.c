// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "api/api.h"
#include "game.h"
#include "lang.h"
#include "map.h"
#include "script.h"
#include "utils.h"

#include "tables/maps.h"
#include "tables/scripts.h"

lua_State* NewLuaState(void) {
    lua_State* l = luaL_newstate();
    if (l == NULL) {
        RuntimeError("cannot create lua state: not enough memory");
    }
    luaopen_string(l);
    luaopen_math(l);
    luaopen_utf8(l);
    APILoadLibs(l);
    return l;
}

static void LuaReport(lua_State* L, int status) {
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

void UpdateAPIConsts(bool first_time) {
    // If this is the first time it's run, we register some useful
    // constants
    if (first_time) {
        // We register the available languages
        lua_pushinteger(gGame.lua_state, GL_English);
        lua_setglobal(gGame.lua_state, "GL_English");
        lua_pushinteger(gGame.lua_state, GL_Spanish);
        lua_setglobal(gGame.lua_state, "GL_Spanish");

        // We register the names of the maps
        for (int i = 0; i < ARR_LEN(MAP_TABLE); i++) {
            Map* map = &MAP_TABLE[i];
            lua_pushinteger(gGame.lua_state, i);
            lua_setglobal(gGame.lua_state, map->name);
        }
    }

    // We register the current game language in use
    lua_pushinteger(gGame.lua_state, gGame.lang);
    lua_setglobal(gGame.lua_state, "GAME_LANG");
}
