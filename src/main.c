// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#include "config.h"

#include "game.h"
#include "hud.h"
#include "script.h"
#include "utils.h"

#include "menus/main_menu.h"
#include "menus/options_menu.h"
#include "menus/pause_menu.h"

int main(void) {
    InitWindow(GAME_DEFAULT_WIDTH, GAME_DEFAULT_HEIGHT, GAME_NAME);
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    tmx_img_load_func = TMX_TextureLoader;
    tmx_img_free_func = TMX_FreeTexture;

    InitGame();

    gGame.state = GS_COPYRIGHT;
    while (!(WindowShouldClose() || gGame.exit)) {
        // --------------= update =--------------
        gGame.frames++;
        gGame.delta_time = GetFrameTime();
        gGame.screen_size = (ScreenSize){GetScreenWidth(), GetScreenHeight()};
        UpdateAPIConsts(false);
        switch (gGame.state) {
            case GS_COPYRIGHT: {
                if (gGame.frames > FRAME) {
                    // 1 second later we go to the main menu
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
                if (IsKeyDown(KEY_ESCAPE)) {
                    gGame.paused = !gGame.paused;
                }
                if (gGame.paused) {
                    ShowCursor();
                    PauseMenu_Update();
                } else {
                    HideCursor();
                    Map_Update();
                    HUD_Update();
                }
            }; break;

            default: {
            }; break;
        }
        // --------------------------------------

        // ---------------= draw =---------------
        BeginDrawing();
        switch (gGame.state) {
            case GS_RUNTIME_ERROR: {
                ShowCursor();
                ClearBackground(BLACK);
                DrawTextS("[" GAME_QUALNAME "] Runtime Error", 30, 30, 22, LIGHTGRAY);
                DrawTextS(gGame.error, 30, 75, 20, LIGHTGRAY);
            }; break;

            case GS_COPYRIGHT: {
                ClearBackground(BLACK);
                DrawTextS(
                    GAME_COPYRIGHT, (gGame.screen_size.height / 2) - 12,
                    (gGame.screen_size.height / 2) - 14, 20, LIGHTGRAY
                );
            }; break;

            case GS_MAIN_MENU: {
                MainMenu_Draw();
            }; break;

            case GS_OPTIONS_MENU: {
                OptionsMenu_Draw();
            }; break;

            case GS_INGAME: {
                if (gGame.paused) {
                    PauseMenu_Draw();
                } else {
                    Map_Draw();
                    HUD_Draw();
                }
            }; break;

            default: {
            }; break;
        }
        EndDrawing();
        // --------------------------------------
    }
    Cleanup();

    CloseWindow();
    return 0;
}
