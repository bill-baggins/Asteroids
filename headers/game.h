#ifndef __GAME_H__
#define __GAME_H__

#include <stc/cstr.h>

typedef struct Game {
    cstr debug_message;
} Game;

Game *Game_new(void);

void Game_get_input(Game *game, float dt);
void Game_update(Game *game, float dt);
void Game_draw(Game *game);
void Game_delete(Game **game);

void Game_run(Game *game);

#endif