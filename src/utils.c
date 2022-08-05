// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>

#include "game.h"

void RuntimeError(const char* msg) {
    if (gGame.state == GS_INGAME) {
        gGame.error = msg;
        gGame.state = GS_RUNTIME_ERROR;
    } else {
        fprintf(stderr, "[Stuge - RuntimeError] %s\n", msg);
        Cleanup();
        exit(1);
    }
}
