// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <lauxlib.h>

#include "../game.h"
#include "../utils.h"

int log_log(int level, lua_State* L) {
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting exactly 1 argument");
    }
    TraceLog(level, luaL_checkstring(L, 1));
    return 0;
}

int log_debug(lua_State* L) {
    return log_log(LOG_DEBUG, L);
}

int log_info(lua_State* L) {
    return log_log(LOG_INFO, L);
}

int log_warn(lua_State* L) {
    return log_log(LOG_WARNING, L);
}

int log_error(lua_State* L) {
    return log_log(LOG_ERROR, L);
}

int log_fatal(lua_State* L) {
    return log_log(LOG_FATAL, L);
}

static const luaL_Reg lib[] = {
    { "debug", log_debug },
    { "info",  log_info  },
    { "warn",  log_warn  },
    { "error", log_error },
    { "fatal", log_fatal },
    { NULL, NULL }
};

int luaopen_log(lua_State* L) {
    luaL_newlib(L, lib);
    return 1;
}
