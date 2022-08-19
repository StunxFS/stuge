// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_GRAPHIC_TABLE_H
#define STUGE_GRAPHIC_TABLE_H

#include <stddef.h>

#include <raylib.h>

#include "../data/data.h"

typedef struct {
    char* filename;
    char* ext;
    char* buf;
    size_t size;
    Image image;
    Texture2D texture;
} StugeGraphic;

static StugeGraphic GRAPHICS_TABLE[] = {
    { "../graphics/backgrounds/bg_main_menu.png", ".png", GRAPHICS_BACKGROUNDS_BG_MAIN_MENU, GRAPHICS_BACKGROUNDS_BG_MAIN_MENU_SIZE },
    { "../graphics/tilesets/basic.png", ".png", GRAPHICS_TILESETS_BASIC, GRAPHICS_TILESETS_BASIC_SIZE },
    { "../graphics/player/player_down.png", ".png", GRAPHICS_PLAYER_PLAYER_DOWN, GRAPHICS_PLAYER_PLAYER_DOWN_SIZE },
    { "../graphics/player/player_left.png", ".png", GRAPHICS_PLAYER_PLAYER_LEFT, GRAPHICS_PLAYER_PLAYER_LEFT_SIZE },
    { "../graphics/player/player_right.png", ".png", GRAPHICS_PLAYER_PLAYER_RIGHT, GRAPHICS_PLAYER_PLAYER_RIGHT_SIZE },
    { "../graphics/player/player_up.png", ".png", GRAPHICS_PLAYER_PLAYER_UP, GRAPHICS_PLAYER_PLAYER_UP_SIZE },
    { "../graphics/player/player_down_left.png", ".png", GRAPHICS_PLAYER_PLAYER_DOWN_LEFT, GRAPHICS_PLAYER_PLAYER_DOWN_LEFT_SIZE },
    { "../graphics/player/player_down_right.png", ".png", GRAPHICS_PLAYER_PLAYER_DOWN_RIGHT, GRAPHICS_PLAYER_PLAYER_DOWN_RIGHT_SIZE },
    { "../graphics/player/player_up_left.png", ".png", GRAPHICS_PLAYER_PLAYER_UP_LEFT, GRAPHICS_PLAYER_PLAYER_UP_LEFT_SIZE },
    { "../graphics/player/player_up_right.png", ".png", GRAPHICS_PLAYER_PLAYER_UP_RIGHT, GRAPHICS_PLAYER_PLAYER_UP_RIGHT_SIZE }
};

#endif // STUGE_GRAPHIC_TABLE_H
