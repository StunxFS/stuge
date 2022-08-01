#include "raylib.h"

int main(void) {
    InitWindow(770, 480, "Stuge - StunxFS's game engine");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("Stuge", 10, 10, 20, LIGHTGRAY);
        DrawText("StunxFS's game engine", 10, 450, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
