// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#include "raygui/raygui.h"

#include "../game.h"
#include "../graphic.h"
#include "../lang.h"

void MainMenu_Update(void) {
    // ...
}

void MainMenu_Draw(void) {
    ClearBackground(BLACK);
    DrawTexture(GetTexture("../graphics/backgrounds/bg_main_menu.png"), 0, 0, WHITE);
    DrawText("Stuge", 30, 30, 40, LIGHTGRAY);

    if (GuiButton((Rectangle){30, gGame.screen_size.height - 140, 200, 33}, _("NewGame"))) {
        gGame.state = GS_INGAME;
    }

    if (GuiButton((Rectangle){30, gGame.screen_size.height - 100, 200, 33}, _("Options"))) {
        ChangeState(GS_OPTIONS_MENU);
    }

    gGame.exit = GuiButton((Rectangle){30, gGame.screen_size.height - 60, 200, 33}, _("Exit"));
}
