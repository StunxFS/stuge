// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_SCRIPT_TABLE_H
#define STUGE_SCRIPT_TABLE_H

#include <stdint.h>

#include "data/scripts_basic.h"

typedef struct {
    char* buf;
    size_t size;
} Script;

static Script SCRIPT_TABLE[] = {
    { SCRIPTS_BASIC, SCRIPTS_BASIC_SIZE }
};

#endif // STUGE_SCRIPT_TABLE_H
