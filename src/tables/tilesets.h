// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_TILESETS_TABLE_H
#define STUGE_TILESETS_TABLE_H

#include "../data/data.h"

typedef struct {
    char* name;
    char* buf;
    int size;
} Tileset;

static Tileset TILESETS_TABLE[] = {
    { "../tilesets/basic.tsx", TILESETS_BASIC, TILESETS_BASIC_SIZE }
};

#endif // STUGE_TILESETS_TABLE_H
