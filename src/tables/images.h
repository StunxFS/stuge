// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_IMAGE_TABLE_H
#define STUGE_IMAGE_TABLE_H

#include <stddef.h>

#include <raylib.h>

#include "../utils.h"

#include "../data/images_basic.h"
#include "../data/images_player_down.h"
#include "../data/images_player_left.h"
#include "../data/images_player_right.h"
#include "../data/images_player_up.h"

typedef struct {
    char* filename;
    char* buf;
    size_t size;
    Image image;
    Texture2D texture;
} StugeImage;

static StugeImage IMAGE_TABLE[] = {
    { "../images/basic.png", IMAGES_BASIC, IMAGES_BASIC_SIZE },
    { "../images/player_down.png", IMAGES_PLAYER_DOWN, IMAGES_PLAYER_DOWN_SIZE },
    { "../images/player_left.png", IMAGES_PLAYER_LEFT, IMAGES_PLAYER_LEFT_SIZE },
    { "../images/player_right.png", IMAGES_PLAYER_RIGHT, IMAGES_PLAYER_RIGHT_SIZE },
    { "../images/player_up.png", IMAGES_PLAYER_UP, IMAGES_PLAYER_UP_SIZE }
};

#endif // STUGE_IMAGE_TABLE_H
