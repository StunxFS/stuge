// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#include "../../thirdparty/raygui/raygui.h"

#include "../game.h"
#include "../lang.h"
#include "../utils.h"

bool OM_back;

void OptionsMenu_Update(void) {
    if (gGame.changed_language) {
        LoadLanguage();
        gGame.changed_language = false;
    } else if (OM_back) {
        SaveConfig();
        ChangeToPrevState();
    }
}

void OptionsMenu_Draw(void) {
    ClearBackground(BLACK);
    DrawTextS(_("Options"), 30, 30, 30, LIGHTGRAY);

    const char* game_lang = _("GameLang");
    GuiLabel((Rectangle){30, 120, 200, 33}, game_lang);
    gGame.changed_language = GuiDropdownBox(
        (Rectangle){TextLength(game_lang) + 170, 120, 200, 33},
        TextJoin(&LANGUAGE_OPTIONS[0], ARR_LEN(LANGUAGE_OPTIONS), ";"),
        (int*)&gGame.config.lang, true
    );

    OM_back = GuiButton((Rectangle){30, gGame.screen_size.height - 60, 200, 33}, _("Back"));
}
