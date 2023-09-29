#include "game.hpp"

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

constexpr int START_ASTEROID_COUNT = 25;

Game::Game()
{
    InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, Constants::TITLE);
    InitAudioDevice();
#ifndef PLATFORM_WEB
    SetTargetFPS(60);
#endif
    SetExitKey(0);

    ResourceHandler::load();
    m_ship = std::make_unique<Ship>();
    m_explosions = {};
    m_asteroids = {};

    for (int i = 0; i < START_ASTEROID_COUNT; i++)
    {
        auto asteroid = Asteroid(TextureSize::LARGE, std::optional<float>(), std::optional<float>());
        m_asteroids.push_back(asteroid);
    }

    m_asteroidSpawnTimer = 0.f;
    m_asteroidSpawnTimerLimit = 7.f;
    m_gameState = GameState::PAUSED;
}

Game::~Game()
{
    CloseAudioDevice();
    ResourceHandler::unload();
    CloseWindow();
}

void Game::update()
{
    if (IsKeyPressed(KEY_ZERO))
    {
        Globals::DEBUG_MODE = !Globals::DEBUG_MODE;
    }
    float dt = GetFrameTime();

    switch (m_gameState)
    {
        case GameState::PAUSED:
            if (IsKeyPressed(KEY_ESCAPE))
            {
                m_gameState = GameState::RUNNING;
            }
            break;
        case GameState::RUNNING:
            CollisionHandler::checkCollisionLaserAsteroid(
                (*m_ship),
                m_ship->m_lasers,
                m_explosions,
                m_asteroids);

            CollisionHandler::checkCollisionShipAsteroid(
                *m_ship,
                m_asteroids
            );

            m_ship->update(dt);
            for (Asteroid& asteroid : m_asteroids)
            {
                asteroid.update(dt);
            }

            for (size_t i = 0; i < m_explosions.size(); )
            {
                Explosion& explosion = m_explosions[i];
                explosion.update(dt);
                if (explosion.isDoneAnimating())
                {
                    m_explosions.erase(m_explosions.begin() + i);
                }
                else
                {
                    i += 1;
                }
            }

            m_asteroidSpawnTimer += dt;
            if (m_asteroidSpawnTimer > m_asteroidSpawnTimerLimit)
            {
                m_asteroidSpawnTimer = 0.f;
                m_asteroids.push_back(
                    Asteroid(TextureSize::LARGE, std::optional<float>(), std::optional<float>())
                );
            }

            if (m_ship->isDead())
            {
                m_explosions.push_back(
                    Explosion(m_ship->m_dest, TextureSize::MEDIUM, ResourceHandler::getSound(TextureSize::LARGE))
                );
                m_gameState = GameState::GAME_OVER;
            }
            break;
        case GameState::GAME_OVER:
            for (Asteroid& asteroid : m_asteroids)
            {
                asteroid.update(dt);
            }

            for (size_t i = 0; i < m_explosions.size(); )
            {
                Explosion& explosion = m_explosions[i];
                explosion.update(dt);
                if (explosion.isDoneAnimating())
                {
                    m_explosions.erase(m_explosions.begin() + i);
                }
                else
                {
                    i += 1;
                }
            }

            if (IsKeyPressed(KEY_R))
            {
                m_ship = std::make_unique<Ship>();
                m_explosions = {};
                m_asteroids = {};

                for (int i = 0; i < START_ASTEROID_COUNT; i++)
                {
                    auto asteroid = Asteroid(TextureSize::LARGE, std::optional<float>(), std::optional<float>());
                    m_asteroids.push_back(asteroid);
                }
                m_gameState = GameState::PAUSED;
            }
            break;
    }
}



void Game::draw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    switch (m_gameState)
    {
        case GameState::PAUSED:
            DrawTexture(ResourceHandler::background, 0, 0, WHITE);
            m_ship->draw();

            DrawText("Welcome to Asteroids!", GetScreenWidth() / 2 - 200, 100, 20, GOLD);
            DrawText("Controls:", GetScreenWidth() / 2 - 200, 120, 20, GOLD);
            DrawText("W - Move forward", GetScreenWidth() / 2 - 200, 140, 20, GOLD);
            DrawText("A/D - Rotate left/right", GetScreenWidth() / 2 - 200, 160, 20, GOLD);
            DrawText("Space - Fire Laser", GetScreenWidth() / 2 - 200, 180, 20, GOLD);
            DrawText("Ready? Press Escape to begin", GetScreenWidth() / 2 - 200, 200, 20, GOLD);

            break;
        case GameState::RUNNING:
            DrawTexture(ResourceHandler::background, 0, 0, WHITE);
            m_ship->draw();

            for (Asteroid& asteroid : m_asteroids)
            {
                asteroid.draw();
            }

            for (Explosion& explosion : m_explosions)
            {
                explosion.draw();
            }

            if (Globals::DEBUG_MODE)
            {
                DrawFPS(0, 0);
            }

            break;
        case GameState::GAME_OVER:
            DrawTexture(ResourceHandler::background, 0, 0, WHITE);

            for (Asteroid& asteroid : m_asteroids)
            {
                asteroid.draw();
            }

            for (Explosion& explosion : m_explosions)
            {
                explosion.draw();
            }

            DrawText("Game Over! Press R to try again", 0, 0, 20, RED);

            if (Globals::DEBUG_MODE)
            {
                DrawFPS(0, 0);
            }
            break;
    }
    EndDrawing();
}

void Game::runWeb(void *data)
{
    Game *game = (Game*)data;
    game->update();
    game->draw();
}

void Game::runDesktop() {
    while (!WindowShouldClose())
    {
        update();
        draw();
    }
}

void Game::run()
{
#ifdef PLATFORM_WEB
    emscripten_set_main_loop_arg(runWeb, (void*)this, 0, 1);
#else
    runDesktop();
#endif
}
