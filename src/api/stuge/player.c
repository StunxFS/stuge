// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "stuge.h"

int stuge_player_look_up(lua_State* L) {
    gGame.player.look = OWL_Up;
    return 0;
}

int stuge_player_look_down(lua_State* L) {
    gGame.player.look = OWL_Down;
    return 0;
}

int stuge_player_look_left(lua_State* L) {
    gGame.player.look = OWL_Left;
    return 0;
}

int stuge_player_look_right(lua_State* L) {
    gGame.player.look = OWL_Right;
    return 0;
}
