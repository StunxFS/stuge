// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "game.h"
#include "player.h"

void Player_Update(void) {
    gGame.player.walk_mode = IsKeyDown(KEY_LEFT_SHIFT)? WM_Run : WM_Walk;
    if (IsKeyDown(KEY_S)) {
        Player_WalkDown();
    } else if (IsKeyDown(KEY_W)) {
        Player_WalkUp();
    } else if (IsKeyDown(KEY_D)) {
        Player_WalkRight();
    } else if (IsKeyDown(KEY_A)) {
        Player_WalkLeft();
    }
}

void Player_Draw(void) {
    switch (gGame.player.look) {
        case OWL_Up: {
            DrawTextureV(gGame.player.face_up, gGame.player.pos, WHITE);
        } break;

        case OWL_Down: {
            DrawTextureV(gGame.player.face_down, gGame.player.pos, WHITE);
        } break;

        case OWL_Left: {
            DrawTextureV(gGame.player.face_left, gGame.player.pos, WHITE);
        } break;

        case OWL_Right: {
            DrawTextureV(gGame.player.face_right, gGame.player.pos, WHITE);
        } break;

        case OWL_UpLeft: {
            DrawTextureV(gGame.player.face_up_left, gGame.player.pos, WHITE);
        } break;

        case OWL_UpRight: {
            DrawTextureV(gGame.player.face_up_right, gGame.player.pos, WHITE);
        } break;

        case OWL_DownLeft: {
            DrawTextureV(gGame.player.face_down_left, gGame.player.pos, WHITE);
        } break;

        case OWL_DownRight: {
            DrawTextureV(gGame.player.face_down_right, gGame.player.pos, WHITE);
        } break;
    }
}

void Player_WalkUp(void) {
    int velocity = (gGame.player.walk_mode == WM_Run)? 8 : 4;
    gGame.player.look = IsKeyDown(KEY_A)? OWL_UpLeft : IsKeyDown(KEY_D)? OWL_UpRight : OWL_Up;
    gGame.player.pos.y -= velocity;
    if (gGame.player.look == OWL_UpLeft) {
        gGame.player.pos.x -= velocity;
    } else if (gGame.player.look == OWL_UpRight) {
        gGame.player.pos.x += velocity;
    }
}

void Player_WalkDown(void) {
    int velocity = (gGame.player.walk_mode == WM_Run)? 8 : 4;
    gGame.player.look = IsKeyDown(KEY_A)? OWL_DownLeft : IsKeyDown(KEY_D)? OWL_DownRight : OWL_Down;
    gGame.player.pos.y += velocity;
    if (gGame.player.look == OWL_DownLeft) {
        gGame.player.pos.x -= velocity;
    } else if (gGame.player.look == OWL_DownRight) {
        gGame.player.pos.x += velocity;
    }
}

void Player_WalkLeft(void) {
    gGame.player.look = IsKeyDown(KEY_W)? OWL_UpLeft : IsKeyDown(KEY_S)? OWL_DownLeft : OWL_Left;
    gGame.player.pos.x -= (gGame.player.walk_mode == WM_Run)? 8 : 4;
}

void Player_WalkRight(void) {
    gGame.player.look = IsKeyDown(KEY_W)? OWL_UpRight : IsKeyDown(KEY_S)? OWL_DownRight : OWL_Right;
    gGame.player.pos.x += (gGame.player.walk_mode == WM_Run)? 8 : 4;
}
