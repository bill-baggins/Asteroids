#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>
#include <optional>
#include <cstdio>
#include <cstdlib>

#include "raylib.h"

#include "ship.hpp"
#include "asteroid.hpp"
#include "resource_handler.hpp"
#include "collision_handler.hpp"
#include "constants.hpp"
#include "globals.hpp"

class Game final
{
public:
    Game();
    ~Game();
    void run();

private:
    void update();
    void draw();

    void runDesktop();
    static void runWeb(void *data);

private:
    GameState m_gameState;
    std::unique_ptr<Ship> m_ship;
    std::vector<Asteroid> m_asteroids;
    std::vector<Explosion> m_explosions;

    float m_asteroidSpawnTimer;
    float m_asteroidSpawnTimerLimit;
};

#endif

