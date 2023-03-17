#include <stdlib.h>
#include "game.h"
#include "globals.h"
#include "raylib.h"

Game *Game_new(void) {
    // Raylib intialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, CAPTION);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    Game *game = malloc(sizeof(Game));
    game->debug_message = cstr_from("Hello! This works!");

    return game;
}

void Game_get_input(Game *game, float dt) {

}

void Game_update(Game *game, float dt) {

}

void Game_draw(Game *game) {
    BeginDrawing(); 

    ClearBackground(DARKGRAY);
    DrawFPS(10, 10);

    DrawText(game->debug_message.lon.data, GetScreenWidth() / 2, GetScreenHeight() / 2, 20, GOLD);

    EndDrawing();
}

void Game_run(Game *game) {
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Game_get_input(game, dt);
        Game_update(game, dt);
        Game_draw(game);
    }
    Game_delete(&game);
}

void Game_delete(Game **game) {
    Game *ref = *game;
    cstr_drop(&ref->debug_message);
    free(*game);
}