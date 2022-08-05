// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <stdlib.h>

#include <raylib.h>

#define RAYLIB_TMX_IMPLEMENTATION
#include "tmx/tmx.h"
#include "tmx/raylib-tmx.h"
#undef RAYLIB_TMX_IMPLEMENTATION

#include "game.h"
#include "image.h"
#include "map.h"
#include "utils.h"

#include "tileset_table.h"
#include "map_table.h"

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
    for (size_t i = 0; i < ARR_LEN(TILESET_TABLE); i++) {
        Tileset* tsx = &TILESET_TABLE[i];
        if (!tmx_load_tileset_buffer(gGame.tmx_resman, tsx->buf, tsx->size, tsx->name)) {
            RuntimeError(
                TextFormat("cannot load tileset '%s': %s", tsx->name, tmx_strerr())
            );
        }
    }
}

void LoadMap(size_t idx) {
    if (idx < 0 || idx >= ARR_LEN(MAP_TABLE)) {
        RuntimeError(TextFormat("cannot load map: index out of range (idx: %d)", idx));
    }
    if (gGame.map_idx != idx) {
        gGame.map_idx = idx;
        gGame.map = &MAP_TABLE[idx];
        if (gGame.map->tmx_map == NULL) {
            gGame.map->tmx_map = tmx_rcmgr_load_buffer(
                gGame.tmx_resman, gGame.map->buf, gGame.map->size
            );
            if (!gGame.map->tmx_map) {
                RuntimeError(TextFormat("cannot load map %d", idx));
            }
        }
    }
}

void Map_Update(void) {
}

void Map_Draw(void) {
    DrawTMX(gGame.map->tmx_map, 0, 0, LIGHTGRAY);
}
