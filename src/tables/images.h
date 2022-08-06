// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_IMAGE_TABLE_H
#define STUGE_IMAGE_TABLE_H

#include <stddef.h>

#include <raylib.h>

#include "../utils.h"

#include "../data/images_basic.h"

typedef struct {
    char* filename;
    char* buf;
    size_t size;
    Image image;
    Texture2D texture;
} StugeImage;

static StugeImage IMAGE_TABLE[] = {
    { "../images/basic.png", IMAGES_BASIC, IMAGES_BASIC_SIZE }
};

#endif // STUGE_IMAGE_TABLE_H
