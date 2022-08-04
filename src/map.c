// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#include "script.h"

void Map_Update(void) {
    RunScript(&SCRIPTS_INIT[0]);
}

void Map_Draw(void) {
    ClearBackground(BLACK);
    DrawText("Stuge [In-Game]", 30, 30, 20, LIGHTGRAY);
}
