// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

// TODO: remove dependency on raygui, and implement own GUI
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

Game gGame;

void InitGame(void) {
    GuiLoadStyleCyber();

    gGame = (Game){
        .frames = 0,
        .delta_time = 0,
        .state = GS_INTERNAL,
        .lang = GAME_DEFAULT_LANG,
        .map_idx = -1,
        .lua_state = NewLuaState(),
        .tmx_resman = tmx_make_resource_manager(),
        .player = {
            .look = OWL_Down,
            .pos = { GAME_DEFAULT_WIDTH / 2, GAME_DEFAULT_HEIGHT / 2 }
        }
    };

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
}

void ChangeState(GameState new_state) {
    gGame.prev_state = gGame.state;
    gGame.state = new_state;
}

void ChangeToPrevState(void) {
    ChangeState(gGame.prev_state);
}

void Cleanup(void) {
    if (gGame.lang_txt != NULL) {
        toml_free(gGame.lang_txt);
    }
    if (gGame.lua_state != NULL) {
        lua_close(gGame.lua_state);
    }
    if (gGame.map != NULL && gGame.map->tmx_map != NULL) {
        tmx_map_free(gGame.map->tmx_map);
    }
    if (gGame.tmx_resman != NULL) {
        tmx_free_resource_manager(gGame.tmx_resman);
    }
}
