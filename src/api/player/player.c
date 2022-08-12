// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "player.h"

int player_look(lua_State* L) {
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting exactly 1 arguments");
    }
    gGame.player.look = luaL_checkinteger(L, 1);
    return 0;
}

static const luaL_Reg lib[] = {
    { "look", player_look },
    { NULL, NULL }
};

int luaopen_player(lua_State* L) {
    luaL_newlib(L, lib);
    return 1;
}
