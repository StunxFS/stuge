// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <stddef.h>

#include <raylib.h>

#include "game.h"

#include "tables/graphics.h"

void LoadGraphics(void) {
    for (size_t i = 0; i < ARR_LEN(GRAPHICS_TABLE); i++) {
        StugeGraphic* im = &GRAPHICS_TABLE[i];
        im->image = LoadImageFromMemory(im->ext, (const unsigned char*)im->buf, im->size);
        im->texture = LoadTextureFromImage(im->image);
    }

    // we load the player textures
    // TODO: For some reason if this is in `InitGame()` it doesn't work as it should
    gGame.player = (OW){
        .face_down = GRAPHICS_TABLE[2].texture,
        .face_left = GRAPHICS_TABLE[3].texture,
        .face_right = GRAPHICS_TABLE[4].texture,
        .face_up = GRAPHICS_TABLE[5].texture,
        .face_down_left = GRAPHICS_TABLE[6].texture,
        .face_down_right = GRAPHICS_TABLE[7].texture,
        .face_up_left = GRAPHICS_TABLE[8].texture,
        .face_up_right = GRAPHICS_TABLE[9].texture
    };
}

static StugeGraphic* GetStugeGraphic(const char* filename) {
    for (size_t i = 0; i < ARR_LEN(GRAPHICS_TABLE); i++) {
        StugeGraphic* im = &GRAPHICS_TABLE[i];
        if (TextIsEqual(im->filename, filename)) {
            return im;
        }
    }
    RuntimeError(TextFormat("GetStugeGraphic: cannot find '%s' graphic", filename));
    return NULL;
}

Image GetImage(const char* filename) {
    return GetStugeGraphic(filename)->image;
}

Texture2D GetTexture(const char* filename) {
    return GetStugeGraphic(filename)->texture;
}
