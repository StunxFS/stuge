// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include "game.h"
#include "player.h"

#include "tables/images.h"

void Player_Update(void) {
    gGame.player.walk_mode = IsKeyDown(KEY_LEFT_SHIFT)? PWM_Run : PWM_Walk;
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
        case PL_Up: {
            DrawTextureV(gGame.player.face_up, gGame.player.pos, RAYWHITE);
        } break;

        case PL_Down: {
            DrawTextureV(gGame.player.face_down, gGame.player.pos, RAYWHITE);
        } break;

        case PL_Left: {
            DrawTextureV(gGame.player.face_left, gGame.player.pos, RAYWHITE);
        } break;

        case PL_Right: {
            DrawTextureV(gGame.player.face_right, gGame.player.pos, RAYWHITE);
        } break;
    }
}

void Player_WalkUp(void) {
    gGame.player.look = PL_Up;
    gGame.player.pos.y -= (gGame.player.walk_mode == PWM_Run)? 8 : 4;
}

void Player_WalkDown(void) {
    gGame.player.look = PL_Down;
    gGame.player.pos.y += (gGame.player.walk_mode == PWM_Run)? 8 : 4;
}

void Player_WalkLeft(void) {
    gGame.player.look = PL_Left;
    gGame.player.pos.x -= (gGame.player.walk_mode == PWM_Run)? 8 : 4;
}

void Player_WalkRight(void) {
    gGame.player.look = PL_Right;
    gGame.player.pos.x += (gGame.player.walk_mode == PWM_Run)? 8 : 4;
}
