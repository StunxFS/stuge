// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_PLAYER_H
#define STUGE_PLAYER_H

typedef enum {
    PL_Up,
    PL_Down,
    PL_Left,
    PL_Right,

    PL_UpLeft,
    PL_UpRight,
    PL_DownLeft,
    PL_DownRight
} PlayerLook;

typedef enum {
    PWM_Walk,
    PWM_Run
} PlayerWalkMode;

typedef struct {
    Texture2D face_up;
    Texture2D face_down;
    Texture2D face_left;
    Texture2D face_right;

    Texture2D face_up_left;
    Texture2D face_up_right;
    Texture2D face_down_left;
    Texture2D face_down_right;

    Vector2 pos;
    PlayerLook look;
    PlayerWalkMode walk_mode;
} Player;

void Player_Update(void);
void Player_Draw(void);

void Player_WalkUp(void);
void Player_WalkDown(void);
void Player_WalkLeft(void);
void Player_WalkRight(void);

#endif // STUGE_PLAYER_H
