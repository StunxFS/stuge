// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "game.h"
#include "ow.h"

void OW_Update(OW* ow) {
    // ...
}

void OW_Draw(OW* ow) {
    switch (ow->look) {
        case OWL_Up: {
            DrawTextureV(ow->face_up, ow->pos, WHITE);
        } break;

        case OWL_Down: {
            DrawTextureV(ow->face_down, ow->pos, WHITE);
        } break;

        case OWL_Left: {
            DrawTextureV(ow->face_left, ow->pos, WHITE);
        } break;

        case OWL_Right: {
            DrawTextureV(ow->face_right, ow->pos, WHITE);
        } break;

        case OWL_UpLeft: {
            DrawTextureV(ow->face_up_left, ow->pos, WHITE);
        } break;

        case OWL_UpRight: {
            DrawTextureV(ow->face_up_right, ow->pos, WHITE);
        } break;

        case OWL_DownLeft: {
            DrawTextureV(ow->face_down_left, ow->pos, WHITE);
        } break;

        case OWL_DownRight: {
            DrawTextureV(ow->face_down_right, ow->pos, WHITE);
        } break;
    }
}

void OW_WalkUp(OW* ow) {
    int velocity = (ow->walk_mode == WM_Run)? 8 : 4;
    ow->pos.y -= velocity;
    if (ow->look == OWL_UpLeft) {
        ow->pos.x -= velocity;
    } else if (ow->look == OWL_UpRight) {
        ow->pos.x += velocity;
    }
}

void OW_WalkDown(OW* ow) {
    int velocity = (ow->walk_mode == WM_Run)? 8 : 4;
    ow->pos.y += velocity;
    if (ow->look == OWL_DownLeft) {
        ow->pos.x -= velocity;
    } else if (ow->look == OWL_DownRight) {
        ow->pos.x += velocity;
    }
}

void OW_WalkLeft(OW* ow) {
    ow->pos.x -= (ow->walk_mode == WM_Run)? 8 : 4;
}

void OW_WalkRight(OW* ow) {
    ow->pos.x += (ow->walk_mode == WM_Run)? 8 : 4;
}
