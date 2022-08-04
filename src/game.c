// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "game.h"

void ChangeState(GameState new_state) {
    gGame.prev_state = gGame.state;
    gGame.state = new_state;
}

void ChangeToPrevState(void) {
    ChangeState(gGame.prev_state);
}

void Cleanup(void) {
    if (gGame.lang_txt != NULL) {
        toml_free(gGame.lang_txt);
    }
    if (gGame.lua_state != NULL) {
        lua_close(gGame.lua_state);
    }
}
