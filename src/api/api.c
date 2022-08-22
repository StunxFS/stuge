// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lauxlib.h>

#include "api.h"

#include "player/player.h"
#include "stuge/stuge.h"

int luaopen_log(lua_State* L);
int luaopen_SharedValues(lua_State* L);

static const luaL_Reg libs[] = {
    { "log", luaopen_log },
    { "stuge", luaopen_stuge },
    { "player", luaopen_player },
    { "SharedValues", luaopen_SharedValues },
    { NULL, NULL }
};

void APILoadLibs(lua_State* L) {
    for (int i = 0; libs[i].name; i++) {
        luaL_requiref(L, libs[i].name, libs[i].func, 1);
    }
}
