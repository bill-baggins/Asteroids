#include <stdlib.h>
#include "game.h"
#include "globals.h"
#include "raylib.h"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

Game *Game_new(void) {
    // Raylib intialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, CAPTION);
    SetWindowTitle(CAPTION);

#ifdef PLATFORM_WEB
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
#endif

    Game *game = malloc(sizeof(Game));
    if (NULL == game) {
        printf("Game failed to initialize. Exiting...");
        exit(1);
    }

    game->debug_message = cstr_from("Hello! This works!");

    return game;
}

void Game_get_input(Game *game) {
    if (IsKeyPressed(KEY_SPACE)) {
        puts("Hi! The spacebar just got pressed.");
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 pos = GetMousePosition();
        printf("X: %.0f, Y: %.0f\n", pos.x, pos.y);
    }
}

void Game_update(Game *game) {

}

void Game_draw(Game *game) {
    BeginDrawing(); 

    ClearBackground(DARKGRAY);
    DrawFPS(10, 10);

    DrawText(game->debug_message.lon.data, GetScreenWidth() / 2, GetScreenHeight() / 2, 20, GOLD);

    EndDrawing();
}

void Game_run_web(void *game_data) {
    Game *game = (Game*)game_data;
    Game_get_input(game);
    Game_update(game);
    Game_draw(game);
}

void Game_run_desktop(Game* game) {
    while (!WindowShouldClose()) {
        Game_get_input(game);
        Game_update(game);
        Game_draw(game);
    }
}

void Game_run(Game *game) {    
#ifdef PLATFORM_WEB
    emscripten_set_main_loop_arg(Game_run_web, game, 0, 1);
#else
    Game_run_desktop(game);
#endif
}

void Game_delete(Game **game) {
    Game *ref = *game;
    cstr_drop(&ref->debug_message);
    free(*game);
}