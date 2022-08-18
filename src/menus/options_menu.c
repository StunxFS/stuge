// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#include "raygui/raygui.h"

#include "../game.h"
#include "../lang.h"
#include "../utils.h"

void OptionsMenu_Update(void) {
    if (gGame.changed_language) {
        LoadLanguage();
        gGame.changed_language = false;
    }
}

void OptionsMenu_Draw(void) {
    ClearBackground(BLACK);
    DrawText(_("Options"), 30, 30, 30, LIGHTGRAY);

    const char* game_lang = _("GameLang");
    GuiLabel((Rectangle){30, 120, 200, 33}, game_lang);
    gGame.changed_language = GuiDropdownBox(
        (Rectangle){TextLength(game_lang) + 170, 120, 200, 33},
        TextJoin(&LANGUAGE_OPTIONS[0], ARR_LEN(LANGUAGE_OPTIONS), ";"),
        (int*)&gGame.config.lang, true
    );

    if (GuiButton((Rectangle){30, gGame.screen_size.height - 60, 200, 33}, _("Back"))) {
        ChangeToPrevState();
    }
}
