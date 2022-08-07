// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_SCRIPTS_H
#define STUGE_SCRIPTS_H

#include <lua.h>

lua_State* NewLuaState(void);
void UpdateAPIConsts(bool first_time);

void RunScript(int idx);

#endif // STUGE_SCRIPTS_H
