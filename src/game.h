// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_GAME_H
#define STUGE_GAME_H

#include "raylib.h"
#include "toml/toml.h"

typedef enum {
    GS_COPYRIGHT,
    GS_MAIN_MENU,
    GS_OPTIONS_MENU,
    GS_EXIT
} GameState;

typedef enum {
    GL_English = 0,
    GL_Spanish
} GameLanguage;

typedef struct {
    int frames;
    Vector2 win_scale;
    GameState state;
    GameState prev_state;
    GameLanguage lang;
    toml_table_t* lang_txt;
} Game;

Game gGame;

void LoadLanguage(void);
const char* txt(const char* key);

void ChangeState(GameState new_state);
void ChangeToPrevState(void);

void Cleanup(void);

#endif // STUGE_GAME_H
