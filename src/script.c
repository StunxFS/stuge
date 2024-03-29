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
    luaopen_base(l);
    luaopen_string(l);
    luaopen_math(l);
    luaopen_utf8(l);
    APILoadLibs(l);
    return l;
}

void UpdateAPIConsts(bool first_time) {
    // If this is the first time it's run, we register some useful
    // constants
    if (first_time) {
        lua_pushinteger(gGame.lua_state, OWL_Up);
        lua_setglobal(gGame.lua_state, "OWL_Up");
        lua_pushinteger(gGame.lua_state, OWL_Down);
        lua_setglobal(gGame.lua_state, "OWL_Down");
        lua_pushinteger(gGame.lua_state, OWL_Left);
        lua_setglobal(gGame.lua_state, "OWL_Left");
        lua_pushinteger(gGame.lua_state, OWL_Right);
        lua_setglobal(gGame.lua_state, "OWL_Right");
        lua_pushinteger(gGame.lua_state, OWL_UpLeft);
        lua_setglobal(gGame.lua_state, "OWL_UpLeft");
        lua_pushinteger(gGame.lua_state, OWL_DownLeft);
        lua_setglobal(gGame.lua_state, "OWL_DownLeft");
        lua_pushinteger(gGame.lua_state, OWL_UpRight);
        lua_setglobal(gGame.lua_state, "OWL_UpRight");
        lua_pushinteger(gGame.lua_state, OWL_DownRight);
        lua_setglobal(gGame.lua_state, "OWL_DownRight");

        lua_pushinteger(gGame.lua_state, GL_English);
        lua_setglobal(gGame.lua_state, "GL_English");
        lua_pushinteger(gGame.lua_state, GL_Spanish);
        lua_setglobal(gGame.lua_state, "GL_Spanish");

        lua_pushinteger(gGame.lua_state, SVK_NIL);
        lua_setglobal(gGame.lua_state, "SVK_NIL");
        lua_pushinteger(gGame.lua_state, SVK_BOOL);
        lua_setglobal(gGame.lua_state, "SVK_BOOL");
        lua_pushinteger(gGame.lua_state, SVK_NUMBER);
        lua_setglobal(gGame.lua_state, "SVK_NUMBER");
        lua_pushinteger(gGame.lua_state, SVK_INTEGER);
        lua_setglobal(gGame.lua_state, "SVK_INTEGER");
        lua_pushinteger(gGame.lua_state, SVK_STRING);
        lua_setglobal(gGame.lua_state, "SVK_STRING");

        for (int i = 0; i < ARR_LEN(MAPS_TABLE); i++) {
            Map* map = &MAPS_TABLE[i];
            lua_pushinteger(gGame.lua_state, i);
            lua_setglobal(gGame.lua_state, map->name);
        }
    }

    // We register the current game language in use
    lua_pushinteger(gGame.lua_state, gGame.config.lang);
    lua_setglobal(gGame.lua_state, "GAME_LANG");
}

static void LuaReport(lua_State* L, int status) {
    if (status != LUA_OK) {
        const char* msg = lua_tostring(L, -1);
        luaL_traceback(L, L, msg, -1);
        RuntimeError(lua_tostring(L, -1));
    }
}

void RunScript(int idx) {
    if (idx < 0 || idx >= ARR_LEN(SCRIPTS_TABLE)) {
        RuntimeError(TextFormat("cannot run script %d (index out of range)", idx));
    }
    LuaReport(gGame.lua_state, luaL_dostring(gGame.lua_state, SCRIPTS_TABLE[idx].buf));
}
