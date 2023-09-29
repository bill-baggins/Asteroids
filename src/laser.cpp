#include "laser.hpp"
#include "resource_handler.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include <cstdio>
#include <cmath>

Laser::Laser(float x, float y, float pAngle)
{
    PlaySound(ResourceHandler::laserFiring);
    Texture& texture = ResourceHandler::laser;
    float width = (float)texture.width;
    float height = (float)texture.height;

    m_src = Rectangle {
        .x = 0,
        .y = 0,
        .width = width,
        .height = height
    };

    m_dest = Rectangle{
        .x = x,
        .y = y,
        .width = width,
        .height = height
    };
    m_hitbox = Rectangle {
        .x = x - width / 2,
        .y = y - height / 2,
        .width = width,
        .height = height
    };

    m_origin = Vector2 {
        m_hitbox.width/2, m_hitbox.height/2
    };

    m_angle = pAngle;
    m_vel = 400.0f;
    m_outOfBounds = false;
}

Laser::~Laser() { }

void Laser::update(float dt)
{
    if (m_hitbox.x < -m_hitbox.x ||
        m_hitbox.x > Constants::SCREEN_WIDTH ||
        m_hitbox.y < -m_hitbox.y ||
        m_hitbox.y > Constants::SCREEN_HEIGHT)
    {
        m_outOfBounds = true;
    }

    m_dest.x -= cosf(DEG2RAD * (m_angle + 90.0)) * m_vel * dt;
    m_dest.y -= sinf(DEG2RAD * (m_angle + 90.0)) * m_vel * dt;

    m_hitbox.x -= cosf(DEG2RAD * (m_angle + 90.0)) * m_vel * dt;
    m_hitbox.y -= sinf(DEG2RAD * (m_angle + 90.0)) * m_vel * dt;
}

void Laser::draw() {
    DrawTexturePro(ResourceHandler::laser, m_src, m_dest, m_origin, m_angle, WHITE);

    if (Globals::DEBUG_MODE)
    {
        DrawRectangleLinesEx(m_dest, 1.f, BLUE);
        DrawRectangleLinesEx(m_hitbox, 1.f, RED);
    }
}

void Laser::setOutOfBounds(bool val)
{
    m_outOfBounds = val;
}

bool Laser::isOutOfBounds()
{
    return m_outOfBounds;
}
