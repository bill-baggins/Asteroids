#include "asteroid.hpp"

#include <cstdio>

#include "constants.hpp"
#include "globals.hpp"

Asteroid::Asteroid(TextureSize pSize, std::optional<float> x, std::optional<float> y)
{
    using namespace Constants;

    m_size = pSize;
    Vector2 frameSize = ResourceHandler::getAsteroidFrameSize(m_size);
    m_frameSizeX = frameSize.x;
    m_frameSizeY = frameSize.y;

    // Corners of the screen
    Vector2 randomSpawnPoints[] =
    {
        Vector2{
            -m_frameSizeX,
            -m_frameSizeY
        },
        Vector2{
            SCREEN_WIDTH + m_frameSizeX,
            -m_frameSizeY
        },
        Vector2{
            -m_frameSizeX,
            SCREEN_HEIGHT + m_frameSizeY
        },
        Vector2{
            SCREEN_WIDTH + m_frameSizeX,
            SCREEN_HEIGHT + m_frameSizeY
        }
    };

    Vector2 destRecOrigin = randomSpawnPoints[GetRandomValue(0, 3)];

    m_src = Rectangle{
        0.0f,
        0.0f,
        m_frameSizeX,
        m_frameSizeY
    };

    if (x.has_value() && y.has_value())
    {
        destRecOrigin.x = x.value();
        destRecOrigin.y = y.value();
    }

    m_dest = Rectangle{
        destRecOrigin.x,
        destRecOrigin.y,
        m_frameSizeX,
        m_frameSizeY
    };

    m_origin = Vector2{
        m_dest.width / 2,
        m_dest.height / 2
    };

    m_hitbox = Rectangle{
        m_dest.x - m_frameSizeX / 2,
        m_dest.y - m_frameSizeY / 2,
        m_frameSizeX - 2,
        m_frameSizeY - 2
    };

    m_vel = Vector2{
        (float)GetRandomValue(-100, 100),
        (float)GetRandomValue(-100, 100)
    };

    if (m_vel.x < 10 && m_vel.x > -10)
    {
        m_vel.x = m_vel.x < 0 ? -20 : 20;
    }

    if (m_vel.y == 0)
    {
        m_vel.y += m_vel.y < 0 ? -20 : 20;
    }

    m_isDestroyed = false;
    m_frameUpdateSpeed = 1.1f;
    m_frameCounter = 0.0f;
    m_frameCounterLimit = 0.052f;
    m_currentFrameX = 0;
    m_currentFrameY = 0;
    m_numberOfFramesX = 16;
    m_numberOfFramesY = 2;
}

Asteroid::~Asteroid() {}

void Asteroid::update(float dt)
{
    animateAsteroid(dt);
    moveAsteroid(dt);
}

void Asteroid::draw()
{
    DrawTexturePro(ResourceHandler::getAsteroidSize(m_size), m_src, m_dest, m_origin, 0.f, WHITE);

    if (Globals::DEBUG_MODE)
    {
        DrawRectangleLinesEx(m_hitbox, 2.f, GREEN);
    }
}

void Asteroid::animateAsteroid(float dt)
{

    m_frameCounter += m_frameUpdateSpeed * dt;
    if (m_frameCounter > m_frameCounterLimit)
    {
        m_frameCounter = 0;

        if (m_currentFrameY == m_numberOfFramesY - 1)
        {
            m_currentFrameY = 0;
        }

        if (m_currentFrameX  == m_numberOfFramesX - 1)
        {
            m_currentFrameX = 0;
        }

        m_src.x = m_currentFrameX * m_frameSizeX;
        m_src.y = m_currentFrameY * m_frameSizeY;

        m_currentFrameX += 1;
        m_currentFrameY += 1;
    }

}

void Asteroid::moveAsteroid(float dt)
{
    using namespace Constants;

    float rightEdge = (float)SCREEN_WIDTH;
    float leftEdge = -m_hitbox.width / 2;
    float topEdge = -m_hitbox.height / 2;
    float bottomEdge = (float)SCREEN_HEIGHT;

    if (m_hitbox.x < leftEdge * 2)
    {
        m_hitbox.x = rightEdge;
        m_dest.x = rightEdge + (m_hitbox.width / 2);
    }
    else if (m_hitbox.x > rightEdge + m_hitbox.width)
    {
        m_hitbox.x = leftEdge;
        m_dest.x = 0;
    }

    if (m_hitbox.y < topEdge * 2)
    {
        m_hitbox.y = bottomEdge;
        m_dest.y = bottomEdge + (m_hitbox.height / 2);
    }
    else if (m_hitbox.y > bottomEdge + m_hitbox.height)
    {
        m_hitbox.y = topEdge;
        m_dest.y = 0;
    }

    m_dest.x += m_vel.x * dt;
    m_dest.y += m_vel.y * dt;
    m_hitbox.x += m_vel.x * dt;
    m_hitbox.y += m_vel.y * dt;
}