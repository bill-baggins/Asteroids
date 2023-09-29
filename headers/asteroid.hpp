#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "raylib.h"
#include "resource_handler.hpp"
#include <optional>

class Asteroid final{
public:
    Asteroid(TextureSize size, std::optional<float> x, std::optional<float> y);
    ~Asteroid();

    void update(float dt);
    void draw();

    void animateAsteroid(float dt);
    void moveAsteroid(float dt);

public:
    Rectangle m_src;
    Rectangle m_dest;
    Rectangle m_hitbox;
    Vector2   m_origin;
    Vector2   m_vel;

    TextureSize m_size;

    float m_frameSizeX;
    float m_frameSizeY;

    bool  m_isDestroyed;
    float m_frameUpdateSpeed;
    float m_frameCounter;
    float m_frameCounterLimit;
    int   m_currentFrameX;
    int   m_currentFrameY;
    int   m_numberOfFramesX;
    int   m_numberOfFramesY;
};

#endif // !ASTEROID_HPP
