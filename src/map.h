// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_MAP_H
#define STUGE_MAP_H

typedef struct {
    char* name;
    char* buf;
    int size;
    int script_idx;
    bool script_executed;
    tmx_map* tmx_map;
} Map;

void* TMX_TextureLoader(const char *path);
void TMX_FreeTexture(void *ptr);

void LoadTilesets(void);
void LoadMap(int idx);

void Map_Update(void);
void Map_Draw(void);

#endif // STUGE_MAP_H
