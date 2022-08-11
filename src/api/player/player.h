// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lauxlib.h>

#include "../../game.h"
#include "../../utils.h"

int luaopen_player(lua_State* L);

int player_look_up(lua_State* L);
int player_look_down(lua_State* L);
int player_look_left(lua_State* L);
int player_look_right(lua_State* L);
