#ifndef LASER_HPP
#define LASER_HPP

#include "raylib.h"

class Laser final
{
public:
    Laser(float x, float y, float angle);
    ~Laser();

    void update(float dt);
    void draw();
    bool isOutOfBounds();
    void setOutOfBounds(bool val);

public:
    Rectangle m_src;
    Rectangle m_dest;
    Rectangle m_hitbox;
    Vector2   m_origin;

    float m_vel;
    float m_angle;
    bool  m_outOfBounds;
};

#endif // !LASER_HPP