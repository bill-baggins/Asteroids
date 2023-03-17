// #include "game.h"
// #include <stc/cstr.h>
#include "raylib.h"
#include <emscripten/emscripten.h>

static void update_draw_frame(void);

int main() {
    InitWindow(800, 600, "Web template");
    emscripten_set_main_loop(update_draw_frame, 0, 1);
    return 0;
}

static void update_draw_frame(void) {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    DrawText("hi", GetScreenWidth() / 2, GetScreenHeight() / 2, RAYWHITE);
    EndDrawing();
}
