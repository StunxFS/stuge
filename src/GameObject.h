// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#ifndef STUGE_GAME_OBJECT_H
#define STUGE_GAME_OBJECT_H

#include "../thirdparty/vector/vector.h"

#include "utils.h"

#define GAME_COMPONENT_FIELDS \
    bool is_active;

#define GAME_MAKE_COMPONENT(COMPONENT_NAME) \
    (Component){ \
        .self = MemDup(&(COMPONENT_NAME){}, sizeof(COMPONENT_NAME)), \
        .IsActive = (void*)COMPONENT_NAME ## _IsActive, \
        .Awake = (void*)COMPONENT_NAME ## _Awake, \
        .Start = (void*)COMPONENT_NAME ## _Start, \
        .Update = (void*)COMPONENT_NAME ## _Update, \
        .LateUpdate = (void*)COMPONENT_NAME ## _LateUpdate, \
        .Draw = (void*)COMPONENT_NAME ## _Draw, \
        .Destroy = (void*)COMPONENT_NAME ## _Destroy \
    }

typedef struct GameObject GameObject;

typedef struct {
    void* self;

    bool (*IsActive)(void*);

    void (*Awake)(struct GameObject*, void*);
    void (*Start)(struct GameObject*, void*);
    void (*Update)(struct GameObject*, void*);
    void (*LateUpdate)(struct GameObject*, void*);
    void (*Draw)(struct GameObject*, void*);
    void (*Destroy)(struct GameObject*, void*);
} Component;

struct GameObject {
    const char* name;
    const char* tag;

    bool is_active;
    bool is_enabled;

    Vector* components;
};

void AwakeGameObjects(void);
void StartGameObjects(void);
void UpdateGameObjects(void);
void LateUpdateGameObjects(void);
void DrawGameObjects(void);
void DestroyGameObjects(void);

#endif // STUGE_GAME_OBJECT_H
