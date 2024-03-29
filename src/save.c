// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <raylib.h>

#include "../thirdparty/cJSON/cJSON.h"

#include "config.h"
#include "game.h"
#include "player.h"

// For saved-games (~/.$(GAME_COMPANY_NAME)/$(GAME_NAME)/saves/SAVE_$(idx).json)

void Load_SaveFile(int idx) {
    if (idx < 0 || idx >= gGame.saves.count) {
        RuntimeError(TextFormat("save index #%d out of range", idx));
        return;
    }

    char* sf_content = LoadFileText(gGame.saves.paths[idx]);
    if (sf_content && sf_content[0] == EOF) {
        RuntimeError(TextFormat("save file #%d is empty", idx));
        return;
    }

    cJSON* save = cJSON_Parse(sf_content);
    if (save == NULL) {
        UnloadFileText(sf_content);
        RuntimeError(TextFormat("cannot parse save file #%d:\n%s", idx, cJSON_GetErrorPtr()));
        return;
    }

    cJSON* map = cJSON_GetObjectItem(save, "map");
    gGame.map_idx = cJSON_GetNumberValue(cJSON_GetObjectItem(map, "idx"));
    bool script_executed = cJSON_GetNumberValue(cJSON_GetObjectItem(map, "script_executed"));

    cJSON* player = cJSON_GetObjectItem(save, "player");
    gGame.player.look = cJSON_GetNumberValue(cJSON_GetObjectItem(player, "look"));
    cJSON* player_pos = cJSON_GetObjectItem(player, "pos");
    gGame.player.pos = (Vector2){
       cJSON_GetNumberValue(cJSON_GetObjectItem(player_pos, "x")),
       cJSON_GetNumberValue(cJSON_GetObjectItem(player_pos, "y"))
    };

    cJSON_Delete(save);
    UnloadFileText(sf_content);

    LoadMap(gGame.map_idx);
    if (gGame.map != NULL) {
        gGame.map->script_executed = script_executed;
    }
}

void Save_SaveFile(int idx) {
    if (idx < 0 || idx >= GAME_DEFAULT_MAX_SAVES) {
        RuntimeError(TextFormat("save index #%d out of range", idx));
    }
    const char* save_file = (idx < gGame.saves.count)? gGame.saves.paths[idx] : TextJoin(
        (const char*[]){ gGame.saves_dir, TextFormat("SAVE_%d.json", idx) }, 2, PATH_SEPARATOR
    );
    FILE* fp = fopen(save_file, "w");
    fprintf(fp,
        "{\n"
        "    \"map\": {\n"
        "        \"idx\": %d,\n"
        "        \"script_executed\": %d\n"
        "    },\n"
        "    \"player\": {\n"
        "        \"look\": %d,\n"
        "        \"pos\": {\n"
        "            \"x\": %f,\n"
        "            \"y\": %f\n"
        "        },\n"
        "    },\n"
        "}\n",
        gGame.map_idx, gGame.map->script_executed,
        gGame.player.look, gGame.player.pos.x, gGame.player.pos.y
    );
    fclose(fp);
}
