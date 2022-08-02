// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "raylib.h"
#include "../raygui/raygui.h"

#include "../game.h"

void MainMenu_Update(void) {
    // ...
}

void MainMenu_Draw(void) {
    ClearBackground(BLACK);
    DrawText("Stuge", 30, 30, 40, LIGHTGRAY);

    if (GuiButton((Rectangle){30, 440, 200, 33}, txt("NewGame"))) {
    }

    if (GuiButton((Rectangle){30, 480, 200, 33}, txt("Options"))) {
        ChangeState(GS_OPTIONS_MENU);
    }

    if (GuiButton((Rectangle){30, 520, 200, 33}, txt("Exit"))) {
        gGame.state = GS_EXIT; // exit
    }
}
