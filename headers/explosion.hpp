#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include <raylib.h>
#include "resource_handler.hpp"

class Explosion final {
public:
    Explosion(Rectangle dest, TextureSize size, Sound sound);
    ~Explosion();

    void update(float dt);
    void draw();
    bool isDoneAnimating();

private:
    bool animate(float dt);

public:
    Rectangle m_src;
    Rectangle m_dest;
    Vector2 m_origin;
    TextureSize m_size;
    bool m_isAnimationDone;

private:
    float m_frameSizeX;
    float m_frameSizeY;


    int m_currentFrameX;
    int m_currentFrameY;
    int m_numberOfFramesX;
    int m_numberOfFramesY;
    float m_frameCounter;
    float m_frameCounterLimit;
};

#endif // !EXPLOSION_HPP

