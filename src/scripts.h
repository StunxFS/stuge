// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_SCRIPTS_H
#define STUGE_SCRIPTS_H

#include <lua.h>

#include "data/scripts_init.h"

lua_State* NewLuaState(void);
void UpdateAPIConsts(void);

void RunScript(char* sc);

#endif // STUGE_SCRIPTS_H
