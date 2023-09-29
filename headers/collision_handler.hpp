#ifndef COLLISION_HANDLER_HPP
#define COLLISION_HANDLER_HPP

#include <deque>
#include <vector>

#include "laser.hpp"
#include "asteroid.hpp"
#include "ship.hpp"
#include "explosion.hpp"

namespace CollisionHandler
{
    void checkCollisionLaserAsteroid(
        Ship& ship,
        std::deque<Laser>& lasers,
        std::vector<Explosion>& explosions,
        std::vector<Asteroid>& asteroids
    );

    void checkCollisionShipAsteroid(
        Ship& ship,
        const std::vector<Asteroid>& asteroids
    );
}

#endif

/**
 * namespace Asteroids.Game.Collision
{
	using static Raylib_CsLo.Raylib;
	using static Asteroids.Game.EntitySize;

	// Handles all logic related to the collision of game objects.
	// It will modify certain attributes of the game objects,
	// namely the List<BulletEntity> and List<AsteroidEntity> collections.
	public static class CollisionHandler
	{
		public static void ManageCollisionListBulletAsteroid(
			ShipEntity ship,
			List<BulletEntity> bullet,
			List<AsteroidEntity> asteroid,
			List<ExplosionEntity> explosion)
		{
			foreach (var b in bullet)
			{
				ManageCollisionBulletAsteroidList(ship, b, asteroid, explosion);
			}
		}

		public static void ManageCollisionShipAsteroidList(
			ShipEntity ship,
			List<AsteroidEntity> asteroids,
			List<ExplosionEntity> explosions)
		{
			if (ship.Health == 0 && ship.Tint.a != 0)
			{
				ship.Tint.a = 0;
				explosions.Add(new ExplosionEntity(ship.DestRec, MEDIUM, GameSound.ShipExplosion));
				return;
			}

			int i = 0;
			while (i < asteroids.Count)
			{
				var asteroid = asteroids[i];
				if (!ship.IsInvincible && CheckCollisionRecs(ship.Hitbox, asteroid.Hitbox))
				{
					ship.GotHit = true;
					ship.IsInvincible = true;
					ship.Health -= 1;
					break;
				}
				i += 1;
			}
		}
		private static void ManageCollisionBulletAsteroidList(
			ShipEntity ship,
			BulletEntity bullet,
			List<AsteroidEntity> asteroids,
			List<ExplosionEntity> explosions)
		{
			int j = 0;
			while (j < asteroids.Count)
			{
				var asteroid = asteroids[j];
				if (CheckCollisionRecs(bullet.Hitbox, asteroid.Hitbox))
				{
					ship.Score += 5;
					if (ship.Score % 250 == 0 && SpawnHandler.AsteroidSpawnCounterLimit > SpawnHandler.MinimumAsteroidSpawnCounterLimit)
					{
						SpawnHandler.AsteroidSpawnCounterLimit -= 0.1f;
					}

					bullet.IsOutOfBounds = true;
					if (asteroid.Size != SMALL)
					{
						// Change the size of the asteroid to be the next smallest.
						EntitySize newSize = asteroid.Size + 1;

						// Create a temporary array of values. These are for convenience in the for loop
						// below.
						var temp = new Vector2[] {
							new Vector2(asteroid.Hitbox.X, asteroid.Hitbox.Y),
							new Vector2(asteroid.Hitbox.X + asteroid.Hitbox.width, asteroid.Hitbox.Y),
							new Vector2(asteroid.Hitbox.X, asteroid.Hitbox.Y + asteroid.Hitbox.height),
							new Vector2(asteroid.Hitbox.X + asteroid.Hitbox.width, asteroid.Hitbox.Y + asteroid.Hitbox.height)
						};

						// Create 4 new asteroids at the corner of the old asteroid.
						for (int k = 0; k < 4; k++)
						{
							asteroids.Add(new AsteroidEntity(newSize, temp[k].X, temp[k].Y));
						}
					}

					// Add an explosion to the list.
					Sound explosionSoundType = asteroid.Size switch
					{
						LARGE => GameSound.LargeAsteroidExplosion,
						MEDIUM => GameSound.MediumAsteroidExplosion,
						SMALL => GameSound.SmallAsteroidExplosion,
						_ => throw new Exception("Asteroid was not LARGE, MEDIUM, or SMALL.")
					};

					explosions.Add(new ExplosionEntity(asteroid.DestRec, asteroid.Size, explosionSoundType));

					// Regardless of the type of asteroid it is, delete it from the list.
					asteroids.RemoveAt(j);

					// I have to return here to ensure that the bullet does not destroy multiple asteroids
					// at once.
					return;
				}
				else
				{
					j += 1;
				}
			}
		}
	}
}
 *
 */