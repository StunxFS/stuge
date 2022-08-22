// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_GAME_H
#define STUGE_GAME_H

#include <lua.h>
#include <raylib.h>

#include "../thirdparty/toml/toml.h"
#include "../thirdparty/tmx/tmx.h"

#include "lang.h"
#include "map.h"
#include "ow.h"
#include "player.h"
#include "SharedValue.h"
#include "utils.h"

typedef enum {
    GS_INTERNAL,
    GS_RUNTIME_ERROR,
    GS_COPYRIGHT,
    GS_MAIN_MENU,
    GS_OPTIONS_MENU,
    GS_INGAME
} GameState;

typedef struct {
    int width;
    int height;
} ScreenSize;

typedef struct {
    GameLanguage lang;
} GameConfig;

typedef struct {
    const char* company_dir;
    const char* saves_dir;
    const char* dir;
    const char* error;

    int frames;
    int delta_time;

    bool paused;
    bool exit;

    GameConfig config;

    ScreenSize screen_size;
    Camera2D main_camera;
    Font font;

    FilePathList saves;

    toml_table_t* lang_txt;
    bool changed_language;

    SharedValue* shared_values;
    lua_State* lua_state;

    GameState state;
    GameState prev_state;

    int map_idx;
    Map* map;
    tmx_resource_manager* tmx_resman;

    OW player;
} Game;

extern Game gGame;

void InitGame(void);

void NewGame(void);

void ChangeState(GameState new_state);
void ChangeToPrevState(void);

void LoadConfig(void);
void SaveConfig(void);
void MakeGameDirectory(void);

void DrawTextS(const char *text, int posX, int posY, int fontSize, Color color);

void Cleanup(void);

#endif // STUGE_GAME_H
