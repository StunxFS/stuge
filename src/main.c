// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"
#undef RAYGUI_IMPLEMENTATION

#include "raygui/styles/cyber/cyber.h"

#include "game.h"
#include "hud.h"
#include "lang.h"
#include "image.h"
#include "map.h"
#include "script.h"

#include "menus/main_menu.h"
#include "menus/options_menu.h"

int main(void) {
    InitWindow(870, 580, "Stuge - StunxFS's game engine");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    tmx_img_load_func = TMX_TextureLoader;
    tmx_img_free_func = TMX_FreeTexture;

    gGame = (Game){
        .frames = 0,
        .state = 0,
        .lang = 0,
        .map_idx = -1,
        .lua_state = NewLuaState(),
        .tmx_resman = tmx_make_resource_manager()
    };

    GuiLoadStyleCyber();
    LoadLanguage();
    LoadImages();
    LoadTilesets();
    UpdateAPIConsts();

    LoadMap(0);

    while (!WindowShouldClose()) {
        // --------------= update =--------------
        gGame.frames++;
        gGame.win_size = (WindowSize){GetScreenWidth(), GetScreenHeight()};
        UpdateAPIConsts();
        switch (gGame.state) {
            case GS_COPYRIGHT: {
                if (gGame.frames > 60) {
                    // 1 second (60f) later we go to the main menu
                    gGame.state = GS_MAIN_MENU;
                }
            }; break;

            case GS_MAIN_MENU: {
                MainMenu_Update();
            }; break;

            case GS_OPTIONS_MENU: {
                OptionsMenu_Update();
            }; break;

            case GS_INGAME: {
                Map_Update();
                HUD_Update();
            }; break;

            case GS_PAUSED: {
            }; break;

            case GS_EXIT: {
                goto EXIT_GAME;
            }; break;
        }
        // --------------------------------------

        // ---------------= draw =---------------
        BeginDrawing();
        switch (gGame.state) {
            case GS_COPYRIGHT: {
                ClearBackground(BLACK);
                DrawText(
                    "(C) 2022 StunxFS. All rights reserved.", gGame.win_size.height - 329,
                    gGame.win_size.height - 290, 20, LIGHTGRAY
                );
            }; break;

            case GS_MAIN_MENU: {
                MainMenu_Draw();
            }; break;

            case GS_OPTIONS_MENU: {
                OptionsMenu_Draw();
            }; break;

            case GS_INGAME: {
                Map_Draw();
                HUD_Draw();
            }; break;

            case GS_PAUSED: {
            }; break;
        }
        EndDrawing();
        // --------------------------------------
    }
EXIT_GAME:
    Cleanup();
    CloseWindow();
    return 0;
}
