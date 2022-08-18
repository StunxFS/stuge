// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#if _WIN32
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif

// TODO: remove dependency on raygui, and implement own GUI
#define RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"
#include "raygui/styles/cyber/cyber.h"
#undef RAYGUI_IMPLEMENTATION

#include "config.h"
#include "game.h"
#include "lang.h"
#include "graphic.h"
#include "map.h"
#include "player.h"
#include "script.h"
#include "utils.h"

Game gGame;

void InitGame(void) {
    GuiLoadStyleCyber();

    const char* home_dir = UserHomeDir();
    gGame = (Game){
        .frames = 0,
        .delta_time = 0,
        .lua_state = NewLuaState(),
        .tmx_resman = tmx_make_resource_manager(),
        .state = GS_INTERNAL,
        .company_dir = TextDup(TextJoin(
            (const char*[]){ home_dir, "." GAME_COMPANY_NAME }, 2, PATH_SEPARATOR
        )),
        .dir = TextDup(TextJoin(
            (const char*[]){ home_dir, "." GAME_COMPANY_NAME, GAME_NAME }, 3,
            PATH_SEPARATOR
        ))
    };

    LoadConfig();
    LoadLanguage();
    LoadGraphics();
    LoadTilesets();

    // For saved games (~/.$(GAME_COMPANY_NAME)/$(GAME_NAME)/saves/SAVE_$(nth).json)
    // TODO: move to a separate function: `void LoadSaveFile(int nth)`
    gGame.map_idx = GAME_DEFAULT_START_MAP;
    gGame.main_camera = (Camera2D){
        .target = (Vector2){ GAME_DEFAULT_WIDTH / 2, GAME_DEFAULT_HEIGHT / 2 },
        .offset = (Vector2){ GAME_DEFAULT_WIDTH / 2, GAME_DEFAULT_HEIGHT / 2 },
        .rotation = 0.0f,
        .zoom = 1.0f
    };
    gGame.player = (OW){
        .look = OWL_Down,
        .pos = { GAME_DEFAULT_WIDTH / 2, GAME_DEFAULT_HEIGHT / 2 },
        .face_down = GRAPHICS_TABLE[2].texture,
        .face_left = GRAPHICS_TABLE[3].texture,
        .face_right = GRAPHICS_TABLE[4].texture,
        .face_up = GRAPHICS_TABLE[5].texture,
        .face_down_left = GRAPHICS_TABLE[6].texture,
        .face_down_right = GRAPHICS_TABLE[7].texture,
        .face_up_left = GRAPHICS_TABLE[8].texture,
        .face_up_right = GRAPHICS_TABLE[9].texture
    };
    LoadMap(gGame.map_idx);

    UpdateAPIConsts(true);
}

void ChangeState(GameState new_state) {
    gGame.prev_state = gGame.state;
    gGame.state = new_state;
}

void ChangeToPrevState(void) {
    ChangeState(gGame.prev_state);
}

void LoadConfig(void) {
    if (DirectoryExists(gGame.dir)) {
        // Take values from the configuration file:
        // (~/.$(GAME_COMPANY_NAME)/$(GAME_NAME)/config.toml)
        static char errbuf[200];
        FILE* fp = fopen(
            TextJoin((const char*[]){ gGame.dir, "config.toml" }, 2, PATH_SEPARATOR), "r"
        );

        toml_table_t* config = toml_parse_file(fp, errbuf, sizeof(errbuf));
        fclose(fp);
        if (config == NULL) {
            RuntimeError(TextFormat("cannot parse configuration file: %s", &errbuf[0]));
        }

        toml_table_t* cfg = toml_table_in(config, "general");
        toml_datum_t value = toml_int_in(cfg, "lang");
        if (value.ok) {
            gGame.config.lang = value.u.i;
        }

        toml_free(config);
    } else {
        // Use default values
        MakeGameDirectory();
        gGame.config = (GameConfig){
            .lang = GAME_DEFAULT_LANG
        };
    }
}

void SaveConfig(void) {
    FILE* fp = fopen(
        TextJoin((const char*[]){ gGame.dir, "config.toml" }, 2, PATH_SEPARATOR), "w"
    );
    fputs("# Configuration file for `" GAME_COMPANY_NAME "." GAME_NAME "`\n\n", fp);
    fputs("[general]\n", fp);
    fprintf(fp, "lang = %d\n", gGame.config.lang);
    fclose(fp);
}

void MakeGameDirectory(void) {
    if (!DirectoryExists(gGame.company_dir)) {
        #if _WIN32
            int r = _mkdir(gGame.company_dir);
        #else
            int r = mkdir(gGame.company_dir, 0777);
        #endif
        if (r == -1) {
            RuntimeError(
                TextFormat(
                    "MakeGameDirectory(): error making company directory: %s", strerror(errno)
                )
            );
            return;
        }
        r = chmod(gGame.company_dir, 0777);
        if (r == -1) {
            RuntimeError(TextFormat("MakeGameDirectory(): chmod error: %s", strerror(errno)));
            return;
        }
    }

    #if _WIN32
        int r = _mkdir(gGame.dir);
    #else
        int r = mkdir(gGame.dir, 0777);
    #endif
    if (r == -1) {
        RuntimeError(TextFormat("MakeGameDirectory(): %s", strerror(errno)));
        return;
    }
    r = chmod(gGame.dir, 0777);
    if (r == -1) {
        RuntimeError(TextFormat("MakeGameDirectory(): chmod error: %s", strerror(errno)));
        return;
    }

    SaveConfig();

    const char* save_dir = TextJoin(
        (const char*[]){ gGame.dir, "saves" }, 2, PATH_SEPARATOR
    );
    #if _WIN32
        r = _mkdir(save_dir);
    #else
        r = mkdir(save_dir, 0777);
    #endif
    if (r == -1) {
        RuntimeError(
            TextFormat(
                "MakeGameDirectory(): error making '%s' directory: %s", save_dir,
                strerror(errno)
            )
        );
        return;
    }
    r = chmod(save_dir, 0777);
    if (r == -1) {
        RuntimeError(TextFormat("MakeGameDirectory(): chmod error: %s", strerror(errno)));
        return;
    }
}

void Cleanup(void) {
    if (gGame.company_dir != NULL) {
        free((void*)gGame.company_dir);
    }
    if (gGame.dir != NULL) {
        free((void*)gGame.dir);
    }
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
