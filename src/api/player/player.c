// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "player.h"

int player_look_up(lua_State* L) {
    gGame.player.look = OWL_Up;
    return 0;
}

int player_look_down(lua_State* L) {
    gGame.player.look = OWL_Down;
    return 0;
}

int player_look_left(lua_State* L) {
    gGame.player.look = OWL_Left;
    return 0;
}

int player_look_right(lua_State* L) {
    gGame.player.look = OWL_Right;
    return 0;
}

static const luaL_Reg lib[] = {
    { "look_up", player_look_up },
    { "look_down", player_look_down },
    { "look_left", player_look_left },
    { "look_right", player_look_right },
    { NULL, NULL }
};

int luaopen_player(lua_State* L) {
    luaL_newlib(L, lib);
    return 1;
}
