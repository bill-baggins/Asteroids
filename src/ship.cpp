#include "ship.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include <cmath>

Ship::Ship()
{
    using namespace Constants;

    Texture& texture = ResourceHandler::ship;

    m_origin = Vector2{
        .x = (float)(texture.width / 2),
        .y = (float)texture.height / 2
    };

    // The destination Rectangle, placed at the texture's center.
    m_dest = Rectangle{
        .x = (float)((SCREEN_WIDTH / 2) - (texture.width / 2)),
        .y = (float)((SCREEN_HEIGHT / 2) - (texture.height / 2)),
        .width = (float)texture.width,
        .height = (float)texture.height
    };

    // Origin rectangle within the texture.
    m_src = Rectangle{
        .x = 0,
        .y = 0,
        .width = (float)texture.width,
        .height = (float)texture.height
    };

    // The m_hitbox, which is an offset of the destination rectangle.
    m_hitbox = Rectangle{
        .x = m_dest.x - (texture.width / 2),
        .y = m_dest.y - (texture.height / 2),
        .width = (float)texture.width,
        .height = (float)texture.height
    };

    m_tint = RAYWHITE;

    m_score = 0;
    m_health = 3;
    m_invulStart = 0.f;
    m_invulEnd = 3.f;
    m_timerIncrement = 0.5f;
    m_isInvulnerable = false;
    m_tintAngle = 0.f;


    m_vel = 0.f;
    m_maxVel = 150.f;
    m_decel = 0.96f;
    m_accel = 150.f;
    m_angle = 0.f;
    m_rotSpeed = 110.f;

    m_gainedHeart = false;
    m_gainedHeartMessageStart = 0.f;
    m_gainedHeartMessageEnd = 5.f;

    m_lasers = {};
}

Ship::~Ship() {}

bool Ship::isDead()
{
    return m_health == 0;
}

void Ship::update(float dt)
{
    moveShip(dt);
    rotateShipLeft(dt);
    rotateShipRight(dt);
    fireLaser(dt);
    checkLaserBounds();
    invulnerabilityTimer(dt);


    if (m_lasers.size() != 0)
    {
        for (Laser& laser : m_lasers)
        {
            laser.update(dt);
        }
    }

    if (m_score != 0 && m_score % 1000 == 0 && m_health < 10)
    {
        m_health += 1;
        m_gainedHeart = true;
    }

    if (m_gainedHeart)
    {
        m_gainedHeartMessageStart += dt;
        if (m_gainedHeartMessageStart > m_gainedHeartMessageEnd)
        {
            m_gainedHeartMessageStart = 0.f;
            m_gainedHeart = false;
        }
    }

}

void Ship::draw()
{
    DrawTexturePro(ResourceHandler::ship, m_src, m_dest, m_origin, m_angle, m_tint);

    // Sin function oscillates how visible it is.
    if (m_isInvulnerable)
    {
        float angle = sinf(m_tintAngle);
        int newTint = abs((int)(angle * 255.f));
        m_tint.b = newTint;
        m_tint.g = newTint;
        m_tintAngle += 0.1f;
        if (m_tintAngle > 2*PI)
        {
            m_tintAngle = 0.f;
        }
    }
    else
    {
        m_tint = RAYWHITE;
    }

    const Texture& heart = ResourceHandler::heart;
    for (size_t i = 0; i < m_health; i++)
    {
        DrawTexture(heart, GetScreenWidth() - (heart.width * (i+1)), 0, RAYWHITE);
    }

    DrawText(TextFormat("Score: %d", m_score), 0, 20, 20, GOLD);


    if (m_lasers.size() != 0)
    {
        for (Laser& laser : m_lasers)
        {
            laser.draw();
        }
    }

    if (m_gainedHeart)
    {
        const char *message = "You gained 1 HP!";
        DrawText(message, (GetScreenWidth() / 2) - (MeasureText(message, 20) / 2), GetScreenHeight() / 2, 20, GOLD);
    }

    if (Globals::DEBUG_MODE)
    {
        DrawRectangleLinesEx(m_hitbox, 2.f, RED);
        DrawText(TextFormat("Velocity: %.2f", m_vel), 0, 40, 20, GOLD);
        DrawText(TextFormat("Laser Count: %llu", m_lasers.size()), 0, 60, 20, GOLD);
    }
}

void Ship::invulnerabilityTimer(float dt)
{
    if (!m_isInvulnerable) { return; }

    m_invulStart += dt;
    if (m_invulStart > m_invulEnd)
    {
        m_invulStart = 0.f;
        m_isInvulnerable = false;
    }
}

void Ship::moveShip(float dt) {
    using namespace Constants;

    if (IsKeyDown(KEY_W) && m_vel < m_maxVel)
    {
        m_vel += m_accel * dt;
    }

    if (IsKeyUp(KEY_W))
    {
        m_vel *= m_decel;
    }

    if (m_dest.x < -m_dest.width)
    {
        m_hitbox.x = (float)SCREEN_WIDTH + (m_hitbox.width / 2);
        m_dest.x = (float)SCREEN_WIDTH + m_dest.width;
    }
    else if (m_dest.x > SCREEN_WIDTH + m_dest.width)
    {
        m_hitbox.x = -m_hitbox.width * 1.5f;
        m_dest.x = -m_dest.width;
    }

    // Bounds checking on the Y-axis for the ship.
    if (m_dest.y < -m_dest.height)
    {
        m_hitbox.y = (float)SCREEN_HEIGHT + (m_hitbox.height / 2);
        m_dest.y = (float)SCREEN_HEIGHT + m_dest.height;
    }
    else if (m_dest.y > SCREEN_HEIGHT + m_dest.height)
    {
        m_hitbox.y = -m_hitbox.height * 1.5f;
        m_dest.y = -m_dest.height;
    }

    m_dest.x -= cosf(DEG2RAD * (m_angle + 90.f)) * m_vel * dt;
    m_dest.y -= sinf(DEG2RAD * (m_angle + 90.f)) * m_vel * dt;

    m_hitbox.x = m_dest.x - (m_dest.width / 2);
	m_hitbox.y = m_dest.y - (m_dest.height / 2);
}

void Ship::rotateShipLeft(float dt)
{
    if (IsKeyDown(KEY_A))
    {
         m_angle -= (m_rotSpeed * dt);
        if (m_angle < -360)
        {
            m_angle *= -1;
            m_angle = (int)m_angle % 360;
        }
    }
}

void Ship::rotateShipRight(float dt)
{
    if (IsKeyDown(KEY_D))
    {
        m_angle += (m_rotSpeed * dt);
        if (m_angle > 360)
        {
            m_angle = (int)m_angle % 360;
        }
    }
}

void Ship::fireLaser(float dt)
{
    if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_Z))
    {
        m_lasers.push_back(Laser(
            cosf(DEG2RAD * (m_angle + 90.0)) + m_dest.x,
            sinf(DEG2RAD * (m_angle + 90.0)) + m_dest.y,
            m_angle
        ));
    }
}

void Ship::checkLaserBounds()
{
    if (m_lasers.size() != 0 && m_lasers.at(0).isOutOfBounds())
    {
        m_lasers.pop_front();
    }
}
