// (C) 2022 StunxFS. All rights reserved. Use of this source code is
// governed by an MIT license that can be found in the LICENSE file.

#include <stdlib.h>

#include "../thirdparty/vector/vector.h"

#include "game.h"
#include "GameObject.h"

void AwakeGameObjects(void) {
    if (gGame.map->game_objects != NULL) {
        VECTOR_FOR_EACH(gGame.map->game_objects, _go) {
            GameObject* go = ITERATOR_GET_AS_PTR(GameObject, &_go);
            if (go->is_active && go->components != NULL) {
                VECTOR_FOR_EACH(go->components, _c) {
                    Component* c = ITERATOR_GET_AS_PTR(Component, &_c);
                    if (c->IsActive(c->self)) {
                        c->Awake(go, c->self);
                    }
                }
            }
        }
    }
}

void StartGameObjects(void) {
    if (gGame.map->game_objects != NULL) {
        VECTOR_FOR_EACH(gGame.map->game_objects, _go) {
            GameObject* go = ITERATOR_GET_AS_PTR(GameObject, &_go);
            if (go->is_active && go->components != NULL) {
                VECTOR_FOR_EACH(go->components, _c) {
                    Component* c = ITERATOR_GET_AS_PTR(Component, &_c);
                    if (c->IsActive(c->self)) {
                        c->Start(go, c->self);
                    }
                }
            }
        }
    }
}

void UpdateGameObjects(void) {
    if (gGame.map->game_objects != NULL) {
        VECTOR_FOR_EACH(gGame.map->game_objects, _go) {
            GameObject* go = ITERATOR_GET_AS_PTR(GameObject, &_go);
            if (go->is_active && go->components != NULL) {
                VECTOR_FOR_EACH(go->components, _c) {
                    Component* c = ITERATOR_GET_AS_PTR(Component, &_c);
                    if (go->is_enabled && c->IsActive(c->self)) {
                        c->Update(go, c->self);
                    }
                }
            }
        }
    }
}

void LateUpdateGameObjects(void) {
    if (gGame.map->game_objects != NULL) {
        VECTOR_FOR_EACH(gGame.map->game_objects, _go) {
            GameObject* go = ITERATOR_GET_AS_PTR(GameObject, &_go);
            if (go->is_active && go->components != NULL) {
                VECTOR_FOR_EACH(go->components, _c) {
                    Component* c = ITERATOR_GET_AS_PTR(Component, &_c);
                    if (go->is_enabled && c->IsActive(c->self)) {
                        c->LateUpdate(go, c->self);
                    }
                }
            }
        }
    }
}

void DrawGameObjects(void) {
    if (gGame.map->game_objects != NULL) {
        VECTOR_FOR_EACH(gGame.map->game_objects, _go) {
            GameObject* go = ITERATOR_GET_AS_PTR(GameObject, &_go);
            if (go->is_active && go->components != NULL) {
                VECTOR_FOR_EACH(go->components, _c) {
                    Component* c = ITERATOR_GET_AS_PTR(Component, &_c);
                    if (go->is_enabled && c->IsActive(c->self)) {
                        c->Draw(go, c->self);
                    }
                }
            }
        }
    }
}

void DestroyGameObjects(void) {
    if (gGame.map->game_objects != NULL) {
        VECTOR_FOR_EACH(gGame.map->game_objects, _go) {
            GameObject* go = ITERATOR_GET_AS_PTR(GameObject, &_go);
            if (go->is_active && go->components != NULL) {
                VECTOR_FOR_EACH(go->components, _c) {
                    Component* c = ITERATOR_GET_AS_PTR(Component, &_c);
                    if (c->IsActive(c->self)) {
                        c->Destroy(go, c->self);
                    }
                    free(c->self);
                }
            }
            if (go->components != NULL) {
                vector_destroy(go->components);
            }
        }
        vector_destroy(gGame.map->game_objects);
    }
}
