// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#include "../game.h"

void PauseMenu_Update(void) {
}

void PauseMenu_Draw(void) {
    DrawRectangleRec(
        (Rectangle){10, 10, gGame.win_size.width - 20,gGame.win_size.height - 20},
        ColorAlpha(BLACK, 0.5)
    );
}
