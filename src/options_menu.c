// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "raylib.h"
#include "gui/raygui.h"

#include "game.h"

void OptionsMenu_Update(void) {
    // ...
}

void OptionsMenu_Draw(void) {
    ClearBackground(BLACK);
    DrawText(txt("Options"), 30, 30, 30, LIGHTGRAY);

    if (GuiButton((Rectangle){30, 520, 200, 33}, txt("Back"))) {
        ChangeToPrevState();
    }
}
