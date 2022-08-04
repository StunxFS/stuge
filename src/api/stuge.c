// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lauxlib.h>

#include "../game.h"
#include "../utils.h"

static const luaL_Reg lib[] = {
    { NULL, NULL }
};

int luaopen_stuge(lua_State *L) {
    luaL_newlib(L, lib);
    return 1;
}
