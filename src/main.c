#include "game.h"

int main(void) {
    Game *game = Game_new();
    Game_run(game);
    Game_delete(&game);
    return 0;
}