// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <stdlib.h>

#include <raylib.h>

#define RAYLIB_TMX_IMPLEMENTATION
#include "tmx/tmx.h"
#include "tmx/raylib-tmx.h"
#undef RAYLIB_TMX_IMPLEMENTATION

#include "game.h"
#include "graphic.h"
#include "map.h"
#include "script.h"
#include "player.h"
#include "utils.h"

#include "tables/tilesets.h"
#include "tables/maps.h"

void set_alloc_functions();

void* TMX_TextureLoader(const char* path) {
    Texture2D* ptr = malloc(sizeof(Texture2D));
    if (ptr != NULL) {
        *ptr = GetTexture(path);
        return ptr;
    }
    return NULL;
}

void TMX_FreeTexture(void* ptr) {
    if (ptr != NULL) {
        UnloadTexture(*((Texture2D*)ptr));
        free(ptr);
    }
}

void LoadTilesets(void) {
    set_alloc_functions();
    for (size_t i = 0; i < ARR_LEN(TILESETS_TABLE); i++) {
        Tileset* tsx = &TILESETS_TABLE[i];
        if (!tmx_load_tileset_buffer(gGame.tmx_resman, tsx->buf, tsx->size, tsx->name)) {
            RuntimeError(
                TextFormat("cannot load tileset '%s': %s", tsx->name, tmx_strerr())
            );
        }
    }
}

void LoadMap(size_t idx) {
    if (idx < 0 || idx >= ARR_LEN(MAPS_TABLE)) {
        RuntimeError(TextFormat("cannot load map: index out of range (idx: %d)", idx));
    }
    if (gGame.map == NULL || gGame.map_idx != idx) {
        gGame.map_idx = idx;
        gGame.map = &MAPS_TABLE[idx];
        if (gGame.map->tmx_map == NULL) {
            gGame.map->tmx_map = tmx_rcmgr_load_buffer(
                gGame.tmx_resman, gGame.map->buf, gGame.map->size
            );
            if (!gGame.map->tmx_map) {
                RuntimeError(TextFormat("cannot load map #%d", idx));
            }
        }
    }
    if (gGame.map == NULL) {
        RuntimeError(TextFormat("cannot load map #%d (null value)", idx));
    }
}

void Map_Update(void) {
    if (!gGame.map->script_executed && gGame.map->script_idx > -1) {
        RunScript(gGame.map->script_idx);
        gGame.map->script_executed = true;
    }
    Player_Update();
    gGame.main_camera.target = (Vector2){ gGame.player.pos.x, gGame.player.pos.y };
    gGame.main_camera.offset = (Vector2){
        gGame.screen_size.width / 2, gGame.screen_size.height / 2
    };
}

void Map_Draw(void) {
    ClearBackground(BLACK);
    BeginMode2D(gGame.main_camera);

    DrawTMX(gGame.map->tmx_map, 0, 0, LIGHTGRAY);
    Player_Draw();

    EndMode2D();
}
