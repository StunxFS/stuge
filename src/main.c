// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"
#include "raygui/styles/cyber/cyber.h"
#undef RAYGUI_IMPLEMENTATION

#include "config.h"

#include "game.h"
#include "hud.h"
#include "lang.h"
#include "graphic.h"
#include "map.h"
#include "player.h"
#include "script.h"

#include "menus/main_menu.h"
#include "menus/options_menu.h"
#include "menus/pause_menu.h"

int main(void) {
    InitWindow(GAME_DEFAULT_WIDTH, GAME_DEFAULT_HEIGHT, GAME_NAME);
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    tmx_img_load_func = TMX_TextureLoader;
    tmx_img_free_func = TMX_FreeTexture;

    gGame = (Game){
        .frames = 0,
        .delta_time = 0,
        .state = 0,
        .lang = 0,
        .map_idx = -1,
        .lua_state = NewLuaState(),
        .tmx_resman = tmx_make_resource_manager(),
        .player = {
            .look = OWL_Down,
            .pos = { GAME_DEFAULT_WIDTH / 2, GAME_DEFAULT_HEIGHT / 2 }
        }
    };

    GuiLoadStyleCyber();

    gGame.main_camera = (Camera2D){
        .target = (Vector2){ gGame.player.pos.x, gGame.player.pos.y },
        .offset = (Vector2){ GAME_DEFAULT_WIDTH / 2, GAME_DEFAULT_HEIGHT / 2 },
        .rotation = 0.0f,
        .zoom = 1.0f
    };

    LoadLanguage();
    LoadGraphics();
    LoadTilesets();
    UpdateAPIConsts(true);

    LoadMap(0);

    gGame.state = GS_COPYRIGHT;
    while (!WindowShouldClose() && !gGame.exit) {
        // --------------= update =--------------
        gGame.frames++;
        gGame.delta_time = GetFrameTime();
        gGame.screen_size = (ScreenSize){GetScreenWidth(), GetScreenHeight()};
        UpdateAPIConsts(false);
        switch (gGame.state) {
            case GS_COPYRIGHT: {
                if (gGame.frames > FRAME) {
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
                ClearBackground(BLACK);
                DrawText("Runtime Error", 30, 30, 35, LIGHTGRAY);
                DrawText(gGame.error, 30, 75, 20, LIGHTGRAY);
            }; break;

            case GS_COPYRIGHT: {
                ClearBackground(BLACK);
                DrawText(
                    "(C) 2022 StunxFS. All rights reserved.", gGame.screen_size.height - 329,
                    gGame.screen_size.height - 290, 20, LIGHTGRAY
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
