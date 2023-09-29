#ifndef SHIP_HPP
#define SHIP_HPP

#include "raylib.h"
#include <cstdio>
#include <deque>
#include "resource_handler.hpp"
#include "laser.hpp"

class Ship final
{
public:
    Ship();
    ~Ship();

    void update(float dt);
    void draw();
    bool isDead();

private:
    void moveShip(float dt);
    void rotateShipLeft(float dt);
    void rotateShipRight(float dt);
    void fireLaser(float dt);
    void checkLaserBounds();
    void invulnerabilityTimer(float dt);

public:
    Rectangle m_dest;
    Rectangle m_src;
    Rectangle m_hitbox;
    Vector2   m_origin;
    Color     m_tint;

    size_t m_score;
    size_t m_health;
    float  m_invulStart;
    float  m_invulEnd;
    float  m_invulAlpha;
    float  m_timerIncrement;
    bool   m_isInvulnerable;
    float  m_tintAngle;

    float m_vel;
    float m_maxVel;
    float m_angle;
    float m_accel;
    float m_decel;

    float m_rotSpeed;

    bool  m_gainedHeart;
    float m_gainedHeartMessageStart;
    float m_gainedHeartMessageEnd;

    std::deque<Laser> m_lasers;
};

#endif // !SHIP_HPP
