#ifndef __GAME_H__
#define __GAME_H__

#include <stc/cstr.h>

typedef struct Game {
    cstr debug_message;
} Game;

Game *Game_new(void);

void Game_get_input(Game *game);
void Game_update(Game *game);
void Game_draw(Game *game);
void Game_delete(Game **game);

void Game_run_desktop(Game* game);
void Game_run(Game *game);
void Game_run_web(void *game_data);

#endif