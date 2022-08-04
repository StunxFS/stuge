// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "raylib.h"
#include "../raygui/raygui.h"

#include "../game.h"
#include "../lang.h"

void MainMenu_Update(void) {
    // ...
}

void MainMenu_Draw(void) {
    ClearBackground(BLACK);
    DrawText("Stuge", 30, 30, 40, LIGHTGRAY);

    if (GuiButton((Rectangle){30, gGame.win_size.height - 140, 200, 33}, _("NewGame"))) {
        gGame.state = GS_INGAME;
    }

    if (GuiButton((Rectangle){30, gGame.win_size.height - 100, 200, 33}, _("Options"))) {
        ChangeState(GS_OPTIONS_MENU);
    }

    if (GuiButton((Rectangle){30, gGame.win_size.height - 60, 200, 33}, _("Exit"))) {
        gGame.state = GS_EXIT; // exit
    }
}
