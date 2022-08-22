// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lauxlib.h>

#include "../config.h"
#include "../game.h"
#include "../SharedValue.h"
#include "../utils.h"

int SharedValues_get(lua_State* L) {
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "`SharedValues.get` expects 1 argument");
    }
    int idx = luaL_checkinteger(L, 1);
    if (idx < 0 || idx >= GAME_DEFAULT_MAX_SHARED_VALUES) {
        return luaL_error(L, "shared value index out of range");
    }
    SharedValue sv = gGame.shared_values[idx];
    switch (sv.kind) {
        case SVK_NIL: {
            lua_pushnil(L);
        }; break;
        case SVK_BOOL: {
            lua_pushboolean(L, sv.b);
        }; break;
        case SVK_NUMBER: {
            lua_pushnumber(L, sv.n);
        }; break;
        case SVK_INTEGER: {
            lua_pushinteger(L, sv.i);
        }; break;
        case SVK_STRING: {
            lua_pushstring(L, sv.s);
        }; break;
        default: {
            return luaL_error(L, "use of uninitialized shared value");
        }; break;
    }
    return 1;
}

int SharedValues_set(lua_State* L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "`SharedValues.set` expects 2 arguments");
    }
    int idx = luaL_checkinteger(L, 1);
    if (idx < 0 || idx >= GAME_DEFAULT_MAX_SHARED_VALUES) {
        return luaL_error(L, "shared value index out of range");
    }
    if (lua_isnil(L, 2)) {
        gGame.shared_values[idx].kind = SVK_NIL;
    } else if (lua_isboolean(L, 2)) {
        gGame.shared_values[idx].kind = SVK_BOOL;
        gGame.shared_values[idx].b = luaL_checkinteger(L, 2);
    } else if (lua_isnumber(L, 2)) {
        gGame.shared_values[idx].kind = SVK_NUMBER;
        gGame.shared_values[idx].n = luaL_checknumber(L, 2);
    } else if (lua_isinteger(L, 2)) {
        gGame.shared_values[idx].kind = SVK_INTEGER;
        gGame.shared_values[idx].i = luaL_checkinteger(L, 2);
    } else if (lua_isstring(L, 2)) {
        gGame.shared_values[idx].kind = SVK_STRING;
        gGame.shared_values[idx].s = luaL_checkstring(L, 2);
    } else {
        return luaL_error(L, "unknown shared value type");
    }
    return 0;
}

int SharedValues_is(lua_State* L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "`SharedValues.is` expects 2 arguments");
    }
    int sv_kind = luaL_checkinteger(L, 1);
    if (sv_kind < 0 || sv_kind >= _SVK_END) {
        return luaL_error(L, "shared value kind out of range");
    }
    int idx = luaL_checkinteger(L, 2);
    if (idx < 0 || idx >= GAME_DEFAULT_MAX_SHARED_VALUES) {
        return luaL_error(L, "shared value index out of range");
    }
    lua_pushboolean(L, gGame.shared_values[idx].kind == sv_kind);
    return 1;
}

static const luaL_Reg lib[] = {
    { "get", SharedValues_get },
    { "set", SharedValues_set },
    { "is",  SharedValues_is  },
    { NULL, NULL }
};

int luaopen_SharedValues(lua_State* L) {
    luaL_newlib(L, lib);
    return 1;
}
