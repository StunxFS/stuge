// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_OW_H
#define STUGE_OW_H

typedef enum {
    WM_Walk,
    WM_Run
} WalkMode;

typedef enum {
    OWL_Up,
    OWL_Down,
    OWL_Left,
    OWL_Right,

    OWL_UpLeft,
    OWL_UpRight,
    OWL_DownLeft,
    OWL_DownRight
} OWLook;

typedef struct {
    OWLook look;
    Vector2 pos;
    WalkMode walk_mode;

    Texture2D face_up;
    Texture2D face_down;
    Texture2D face_left;
    Texture2D face_right;

    Texture2D face_up_left;
    Texture2D face_up_right;
    Texture2D face_down_left;
    Texture2D face_down_right;
} OW;

#endif // STUGE_OW_H
