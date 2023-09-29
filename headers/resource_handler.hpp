#ifndef RESOURCE_HANDLER_HPP
#define RESOURCE_HANDLER_HPP

#include "raylib.h"

// For specifying animation frame sizes.
enum TextureSize
{
    LARGE = 0b1000100,
    MEDIUM,
    SMALL
};

namespace ResourceHandler
{
    inline Texture background;
    inline Texture ship;
    inline Texture laser;
    inline Texture heart;

    inline Texture largeAsteroidAtlas;
    inline Texture mediumAsteroidAtlas;
    inline Texture smallAsteroidAtlas;

    inline Texture largeExplosionAtlas;
    inline Texture mediumExplosionAtlas;
    inline Texture smallExplosionAtlas;

    inline Sound largeAsteroidExplosion;
    inline Sound mediumAsteroidExplosion;
    inline Sound smallAsteroidExplosion;
    inline Sound shipExplosion;
    inline Sound laserFiring;
    inline Sound shipHit;

    void load();
    void unload();

    Texture getAsteroidSize(TextureSize size);
    Texture getExplosionSize(TextureSize size);

    Vector2 getAsteroidFrameSize(TextureSize size);
    Vector2 getExplosionFrameSize(TextureSize size);

    Sound getSound(TextureSize size);
}

#endif // !RESOURCE_HANDLER_HPP

