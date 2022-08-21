// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#include "../../thirdparty/raygui/raygui.h"

#include "../game.h"
#include "../graphic.h"
#include "../lang.h"
#include "../save.h"

bool MM_new_game;
bool MM_options;

void MainMenu_Update(void) {
    if (MM_new_game) {
        gGame.state = GS_INGAME;
        NewGame();
    } else if (MM_options) {
        ChangeState(GS_OPTIONS_MENU);
    }
}

void MainMenu_Draw(void) {
    ClearBackground(BLACK);
    DrawTexture(GetTexture("../graphics/backgrounds/bg_main_menu.png"), 0, 0, WHITE);
    DrawTextS("Stuge", 30, 30, 40, LIGHTGRAY);

    MM_new_game = GuiButton((Rectangle){30, gGame.screen_size.height - 140, 200, 33}, _("NewGame"));
    MM_options = GuiButton((Rectangle){30, gGame.screen_size.height - 100, 200, 33}, _("Options"));
    gGame.exit = GuiButton((Rectangle){30, gGame.screen_size.height - 60, 200, 33}, _("Exit"));
}
