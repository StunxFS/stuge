// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_GAME_H
#define STUGE_GAME_H

#include <stdint.h>

#include <lua.h>
#include <raylib.h>

#include "toml/toml.h"
#include "tmx/tmx.h"

#include "lang.h"
#include "map.h"

typedef enum {
    GS_INTERNAL,
    GS_RUNTIME_ERROR,
    GS_COPYRIGHT,
    GS_MAIN_MENU,
    GS_OPTIONS_MENU,
    GS_INGAME,
    GS_EXIT
} GameState;

typedef struct {
    int width;
    int height;
} WindowSize;

typedef struct {
    int frames;
    bool paused;
    WindowSize win_size;

    const char* error;

    GameLanguage lang;
    toml_table_t* lang_txt;
    bool changed_language;

    lua_State* lua_state;

    GameState state;
    GameState prev_state;

    size_t map_idx;
    Map* map;
    tmx_resource_manager* tmx_resman;
} Game;

extern Game gGame;

void ChangeState(GameState new_state);
void ChangeToPrevState(void);

void Cleanup(void);

#endif // STUGE_GAME_H
