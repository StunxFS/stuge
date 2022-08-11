// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lauxlib.h>

#include "stuge.h"

static const luaL_Reg lib[] = {
    { "player_look_up", stuge_player_look_up },
    { "player_look_down", stuge_player_look_down },
    { "player_look_left", stuge_player_look_left },
    { "player_look_right", stuge_player_look_right },
    { NULL, NULL }
};

int luaopen_stuge(lua_State* L) {
    luaL_newlib(L, lib);
    return 1;
}
