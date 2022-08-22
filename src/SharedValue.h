// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_SHARED_VALUE_H
#define STUGE_SHARED_VALUE_H

#include <lua.h>

typedef enum {
    SVK_NIL,
    SVK_BOOL,
    SVK_NUMBER,
    SVK_INTEGER,
    SVK_STRING,
    _SVK_END
} SharedValueKind;

typedef struct {
    SharedValueKind kind;
    union {
        bool b;
        lua_Number n;
        lua_Integer i;
        const char* s;
    };
} SharedValue;

#endif // STUGE_SHARED_VALUE_H
