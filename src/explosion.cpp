#include "explosion.hpp"

Explosion::Explosion(Rectangle dest, TextureSize size, Sound sound)
{
    PlaySound(sound);

    auto frameSize = ResourceHandler::getExplosionFrameSize(size);
    m_frameSizeX = frameSize.x;
    m_frameSizeY = frameSize.y;

    m_src = Rectangle{
        0,
        0,
        m_frameSizeX,
        m_frameSizeY
    };

    m_dest = Rectangle{
        dest.x,
        dest.y,
        m_frameSizeX,
        m_frameSizeY
    };

    m_origin = Vector2{
        m_frameSizeX / 2,
        m_frameSizeY / 2
    };

    m_size = size;

    m_isAnimationDone = false;
    m_currentFrameX = 0;
    m_currentFrameY = 0;
    m_numberOfFramesX = 8;
    m_numberOfFramesY = 8;

    m_frameCounter = 0.0f;
    m_frameCounterLimit = 0.005f;
}

Explosion::~Explosion() {}

void Explosion::update(float dt)
{
    bool isDoneAnimating = animate(dt);
    if (isDoneAnimating)
    {
        m_isAnimationDone = true;
    }
}

bool Explosion::isDoneAnimating()
{
    return m_isAnimationDone;
}

void Explosion::draw()
{
    DrawTexturePro(
        ResourceHandler::getExplosionSize(this->m_size),
        m_src,
        m_dest,
        m_origin,
        0.0f,
        WHITE
    );
}

bool Explosion::animate(float dt)
{
    // Guard clause to ensure that the animation does not continue forever.
    if (m_currentFrameX == m_numberOfFramesX && m_currentFrameY == m_numberOfFramesY)
    {
        return true;
    }

    m_frameCounter += dt;
    if (m_frameCounter > m_frameCounterLimit)
    {
        m_frameCounter = 0;

        if (m_currentFrameX == m_numberOfFramesX)
        {
            m_currentFrameX = 0;
            m_currentFrameY += 1;
        }
        else
        {
            m_currentFrameX += 1;
        }

        m_src.x = m_currentFrameX * m_frameSizeX;
        m_src.y = m_currentFrameY * m_frameSizeY;
    }

    return false;
}