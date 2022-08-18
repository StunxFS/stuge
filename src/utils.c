// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>

#include "config.h"
#include "game.h"
#include "utils.h"

void RuntimeError(const char* msg) {
    if (gGame.state == GS_INGAME) {
        gGame.state = GS_RUNTIME_ERROR;
        gGame.error = msg;
    } else {
        fprintf(stderr, "[" GAME_COMPANY_NAME "." GAME_NAME "] Runtime Error: %s\n", msg);
        Cleanup();
        exit(1);
    }
}

char* UserHomeDir(void) {
    #if _WIN32
        return getenv("USERPROFILE");
    #else
        return getenv("HOME");
    #endif
}

char* TextDup(const char* str) {
    int size = strlen(str);
    char* buf = malloc(size + 1);
    memcpy(buf, str, size);
    buf[size] = 0;
    return buf;
}
