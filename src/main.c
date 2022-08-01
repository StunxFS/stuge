// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "raylib.h"

#include "game.h"
#include "main_menu.h"

Game gGame;

int main(void) {
    InitWindow(870, 580, "Stuge - StunxFS's game engine");
    SetExitKey(KEY_NULL);

    gGame = (Game){
        .frames = 0,
        .state = 0
    };

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        // --------------= update =--------------
        gGame.frames++;
        gGame.win_scale = GetWindowScaleDPI();
        switch (gGame.state) {
            case GS_COPYRIGHT: {
                if (gGame.frames > 120) {
                    // 2 seconds (120f) later we go to the main menu
                    gGame.state = GS_MAIN_MENU;
                }
            }; break;
            case GS_MAIN_MENU: {
                MainMenu_Update();
            } break;
        }
        // --------------------------------------

        // ---------------= draw =---------------
        BeginDrawing();
        switch (gGame.state) {
            case GS_COPYRIGHT: {
                ClearBackground(BLACK);
                DrawText("(C) 2022 StunxFS. All rights reserved.", 239, 280, 20, LIGHTGRAY);
            }; break;
            case GS_MAIN_MENU: {
                MainMenu_Draw();
            }; break;
        }
        EndDrawing();
        // --------------------------------------
    }

    CloseWindow();
    return 0;
}
