// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

typedef enum {
    GS_COPYRIGHT,
    GS_MAIN_MENU
} GameState;

typedef struct {
    int frames;
    GameState state;
    Vector2 win_scale;
} Game;
