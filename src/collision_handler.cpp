#include "collision_handler.hpp"
#include <iostream>

void CollisionHandler::checkCollisionLaserAsteroid(
    Ship& ship,
    std::deque<Laser>& lasers,
    std::vector<Explosion>& explosions,
    std::vector<Asteroid>& asteroids
)
{
    for (size_t i = 0; i < lasers.size();)
    {
        Laser& laser = lasers.at(i);

        for (size_t j = 0; j < asteroids.size();)
        {
            Asteroid& asteroid = asteroids.at(j);
            if (CheckCollisionRecs(laser.m_hitbox, asteroid.m_hitbox))
            {
                laser.m_outOfBounds = true;
                ship.m_score += 5;
                if (ship.m_score % 250 == 0 && ship.m_health > 10) 
                {
                    ship.m_health += 1;
                }

                if (asteroid.m_size != TextureSize::SMALL)
                {
                    TextureSize nextSize = (TextureSize)((int)asteroid.m_size + 1);
                    // Create a temporary array of values. These are for convenience in the for loop
                    // below.


                    Vector2 temp[] =
                    {
                        Vector2{asteroid.m_hitbox.x, asteroid.m_hitbox.y},
                        Vector2{asteroid.m_hitbox.x + asteroid.m_hitbox.width, asteroid.m_hitbox.y},
                        Vector2{asteroid.m_hitbox.x, asteroid.m_hitbox.y + asteroid.m_hitbox.height},
                        Vector2{asteroid.m_hitbox.x + asteroid.m_hitbox.width, asteroid.m_hitbox.y + asteroid.m_hitbox.height}
                    };

                    // Create 4 new asteroids at the corner of the old asteroid.
                    for (int k = 0; k < 4; k++)
                    {
                        asteroids.push_back(Asteroid(nextSize, temp[k].x, temp[k].y));
                    }
                }

                // Add an explosion to the list.
                Sound explosionSound = ResourceHandler::getSound(asteroid.m_size);

                explosions.push_back(Explosion(asteroid.m_dest, asteroid.m_size, explosionSound));

                // Regardless of the type of asteroid it is, delete it from the list.
                asteroids.erase(asteroids.begin() + j);

                // break here to prevent the laser from continuing on to destroy multiple
                // asteroids.
                break;
            }
            else
            {
                j += 1;
            }
        }

        if (laser.isOutOfBounds())
        {
            lasers.erase(lasers.begin() + i);
        }
        else
        {
            i += 1;
        }
    }
}

void CollisionHandler::checkCollisionShipAsteroid(
    Ship& ship,
    const std::vector<Asteroid>& asteroids
)
{
    for (const Asteroid& asteroid : asteroids)
    {
        if (!ship.m_isInvulnerable && CheckCollisionRecs(ship.m_hitbox, asteroid.m_hitbox))
        {
            ship.m_health -= 1;
            ship.m_isInvulnerable = true;
            break;
        }
    }
}