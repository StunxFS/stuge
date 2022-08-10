// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_IMAGE_TABLE_H
#define STUGE_IMAGE_TABLE_H

#include <stddef.h>

#include <raylib.h>

#include "../utils.h"

#include "../data/data.h"

typedef struct {
    char* filename;
    char* buf;
    size_t size;
    Image image;
    Texture2D texture;
} StugeImage;

static StugeImage IMAGE_TABLE[] = {
    { "../images/backgrounds/bg_main_menu.png", IMAGES_BACKGROUNDS_BG_MAIN_MENU, IMAGES_BACKGROUNDS_BG_MAIN_MENU_SIZE },
    { "../images/tilesets/basic.png", IMAGES_TILESETS_BASIC, IMAGES_TILESETS_BASIC_SIZE },
    { "../images/player/player_down.png", IMAGES_PLAYER_PLAYER_DOWN, IMAGES_PLAYER_PLAYER_DOWN_SIZE },
    { "../images/player/player_left.png", IMAGES_PLAYER_PLAYER_LEFT, IMAGES_PLAYER_PLAYER_LEFT_SIZE },
    { "../images/player/player_right.png", IMAGES_PLAYER_PLAYER_RIGHT, IMAGES_PLAYER_PLAYER_RIGHT_SIZE },
    { "../images/player/player_up.png", IMAGES_PLAYER_PLAYER_UP, IMAGES_PLAYER_PLAYER_UP_SIZE }
};

#endif // STUGE_IMAGE_TABLE_H
