#include "raylib/raylib.h"
#include "raylib/rlgl.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1500, 1000, "Gefest");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }

    CloseWindow();
}
