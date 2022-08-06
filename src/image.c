// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <stddef.h>

#include <raylib.h>

#include "tables/images.h"

void LoadImages(void) {
    for (size_t i = 0; i < ARR_LEN(IMAGE_TABLE); i++) {
        StugeImage* im = &IMAGE_TABLE[0];
        im->image = LoadImageFromMemory(".png", (const unsigned char*)im->buf, im->size);
        im->texture = LoadTextureFromImage(im->image);
    }
}

Texture2D GetTexture(const char* filename) {
    for (size_t i = 0; i < ARR_LEN(IMAGE_TABLE); i++) {
        StugeImage* im = &IMAGE_TABLE[0];
        if (TextIsEqual(im->filename, filename)) {
            return im->texture;
        }
    }
    RuntimeError(TextFormat("GetTexture: cannot find '%s' texture", filename));
}
