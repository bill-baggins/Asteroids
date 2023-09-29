#include "game.hpp"
#include <memory>

int main(void)
{
    auto game = std::make_unique<Game>();
    game->run();

    return 0;
}
