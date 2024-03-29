// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_IMAGE_H
#define STUGE_IMAGE_H

#include "tables/graphics.h"

void LoadGraphics(void);

Image GetImage(const char* filename);
Texture2D GetTexture(const char* filename);

#endif // STUGE_IMAGE_H
