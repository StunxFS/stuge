// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <stddef.h>

#include <raylib.h>

#include "game.h"

#include "tables/images.h"

void LoadImages(void) {
    for (size_t i = 0; i < ARR_LEN(IMAGE_TABLE); i++) {
        StugeImage* im = &IMAGE_TABLE[i];
        im->image = LoadImageFromMemory(".png", (const unsigned char*)im->buf, im->size);
        im->texture = LoadTextureFromImage(im->image);
    }
    gGame.player.face_down = IMAGE_TABLE[1].texture;
    gGame.player.face_left = IMAGE_TABLE[2].texture;
    gGame.player.face_right = IMAGE_TABLE[3].texture;
    gGame.player.face_up = IMAGE_TABLE[4].texture;
}

Texture2D GetTexture(const char* filename) {
    for (size_t i = 0; i < ARR_LEN(IMAGE_TABLE); i++) {
        StugeImage* im = &IMAGE_TABLE[0];
        if (TextIsEqual(im->filename, filename)) {
            return im->texture;
        }
    }
    RuntimeError(TextFormat("GetTexture: cannot find '%s' texture", filename));
    return (Texture2D){};
}
