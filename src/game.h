// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_GAME_H
#define STUGE_GAME_H

#include <lua.h>
#include <raylib.h>

#include "toml/toml.h"

#include "lang.h"

typedef enum {
    GS_COPYRIGHT,
    GS_MAIN_MENU,
    GS_OPTIONS_MENU,
    GS_INGAME,
    GS_PAUSED,
    GS_EXIT
} GameState;

typedef struct {
    int width;
    int height;
} WindowSize;

typedef struct {
    int frames;
    WindowSize win_size;

    GameLanguage lang;
    toml_table_t* lang_txt;
    bool changed_language;

    lua_State* lua_state;

    GameState state;
    GameState prev_state;
} Game;

Game gGame;

void ChangeState(GameState new_state);
void ChangeToPrevState(void);

void Cleanup(void);

#endif // STUGE_GAME_H
