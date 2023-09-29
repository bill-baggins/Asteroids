#include "resource_handler.hpp"
#include "raylib.h"
#include "constants.hpp"
#include <cstdio>


void ResourceHandler::load()
{
    // Load images.
    Image shipIm = LoadImage("resources/spaceship.png");
    Image backgroundIm = LoadImage("resources/space.png");
    Image laserIm = LoadImage("resources/laser.png");
    Image heartIm = LoadImage("resources/heart.png");

    Image largeAsteroidAtlasIm = LoadImage("resources/animated_asteroid.png");
    Image mediumAsteroidAtlasIm = LoadImage("resources/animated_asteroid.png");
    Image smallAsteroidAtlasIm = LoadImage("resources/animated_asteroid.png");

    Image largeExplosionAtlasIm = LoadImage("resources/animated_explosion.png");
    Image mediumExplosionAtlasIm = LoadImage("resources/animated_explosion.png");
    Image smallExplosionAtlasIm = LoadImage("resources/animated_explosion.png");

    // Do necessary image adjustments.
    float ship_scale = 0.3f;

    // Make the ship smaller.
    ImageResize(&shipIm, (int)((float)shipIm.width * ship_scale), (int)((float)shipIm.height * ship_scale));

    // Set the background to the size of the screen.
    ImageResize(&backgroundIm, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);

    // Make the laser small and thin enough to be classfied as a laser.
    ImageResize(&laserIm, shipIm.width / 10, shipIm.height / 5);

    // Resizing the heart.
    ImageResize(&heartIm, heartIm.width / 4, heartIm.height / 4);

    // Creating the sizes for each of the asteroid atlases.
    ImageResize(&mediumAsteroidAtlasIm, largeAsteroidAtlasIm.width / 2, largeAsteroidAtlasIm.height / 2);
    ImageResize(&smallAsteroidAtlasIm, 288, 40);

    // Creating the sizes for each of the explosion atlases.
    ImageResize(&mediumExplosionAtlasIm, 540, 540);
    ImageResize(&smallExplosionAtlasIm, 270, 270);


    // Turn images into textures.
    ship = LoadTextureFromImage(shipIm);
    background = LoadTextureFromImage(backgroundIm);
    laser = LoadTextureFromImage(laserIm);
    heart = LoadTextureFromImage(heartIm);

    largeAsteroidAtlas = LoadTextureFromImage(largeAsteroidAtlasIm);
    mediumAsteroidAtlas = LoadTextureFromImage(mediumAsteroidAtlasIm);
    smallAsteroidAtlas = LoadTextureFromImage(smallAsteroidAtlasIm);

    largeExplosionAtlas = LoadTextureFromImage(largeExplosionAtlasIm);
    mediumExplosionAtlas = LoadTextureFromImage(mediumExplosionAtlasIm);
    smallExplosionAtlas = LoadTextureFromImage(smallExplosionAtlasIm);


    // Unload images.
    UnloadImage(shipIm);
    UnloadImage(backgroundIm);
    UnloadImage(laserIm);
    UnloadImage(heartIm);
    UnloadImage(largeAsteroidAtlasIm);
    UnloadImage(mediumAsteroidAtlasIm);
    UnloadImage(smallAsteroidAtlasIm);
    UnloadImage(largeExplosionAtlasIm);
    UnloadImage(mediumExplosionAtlasIm);
    UnloadImage(smallExplosionAtlasIm);

    // Now load sounds...
    Wave largeAsteroidExplosionWave = LoadWave("resources/explosion.wav");
    Wave mediumAsteroidExplosionWave = LoadWave("resources/explosion.wav");
    Wave smallAsteroidExplosionWave = LoadWave("resources/explosion.wav");
    Wave shipExplosionWave = LoadWave("resources/explosion.wav");
    Wave laserFiringWave = LoadWave("resources/laser.wav");
    Wave shipHitWave = LoadWave("resources/ship_hit.wav");

    largeAsteroidExplosion = LoadSoundFromWave(largeAsteroidExplosionWave);
    SetSoundVolume(largeAsteroidExplosion, 0.25f);
    SetSoundPitch(largeAsteroidExplosion, 0.2f);

    mediumAsteroidExplosion = LoadSoundFromWave(mediumAsteroidExplosionWave);
    SetSoundVolume(mediumAsteroidExplosion, 0.25f);
    SetSoundPitch(mediumAsteroidExplosion, 0.4f);

    smallAsteroidExplosion = LoadSoundFromWave(smallAsteroidExplosionWave);
    SetSoundVolume(smallAsteroidExplosion, 0.25f);

    shipExplosion = LoadSoundFromWave(shipExplosionWave);
    SetSoundVolume(shipExplosion, 0.25f);
    SetSoundPitch(shipExplosion, 0.25f);

    laserFiring = LoadSoundFromWave(laserFiringWave);
    SetSoundVolume(laserFiring, 0.1f);

    shipHit = LoadSoundFromWave(shipHitWave);
    SetSoundVolume(shipHit, 1.0f);
    SetSoundPitch(shipHit, 1.3f);

    UnloadWave(largeAsteroidExplosionWave);
    UnloadWave(mediumAsteroidExplosionWave);
    UnloadWave(smallAsteroidExplosionWave);
    UnloadWave(shipExplosionWave);
    UnloadWave(laserFiringWave);
    UnloadWave(shipHitWave);
}

Texture ResourceHandler::getAsteroidSize(TextureSize size)
{
    Texture texture = largeAsteroidAtlas;
    switch (size) {
    case LARGE:
        break;
    case MEDIUM:
        texture = mediumAsteroidAtlas;
        break;
    case SMALL:
        texture = smallAsteroidAtlas;
        break;
    default:
        puts("How'd you get here?");
        break;
    }
    return texture;
}

Texture ResourceHandler::getExplosionSize(TextureSize size)
{
    Texture texture = largeExplosionAtlas;
    switch (size) {
    case LARGE:
        break;
    case MEDIUM:
        texture = mediumExplosionAtlas;
        break;
    case SMALL:
        texture = smallExplosionAtlas;
        break;
    default:
        puts("How'd you get here?");
        break;
    }
    return texture;
}

Vector2 ResourceHandler::getAsteroidFrameSize(TextureSize size)
{
    Vector2 frameSize = Vector2{(float)largeAsteroidAtlas.width / 16, (float)largeAsteroidAtlas.height / 2};
    switch (size) {
    case LARGE:
        break;
    case MEDIUM:
        frameSize = Vector2{(float)mediumAsteroidAtlas.width / 16, (float)mediumAsteroidAtlas.height / 2};
        break;
    case SMALL:
        frameSize = Vector2{(float)smallAsteroidAtlas.width / 16, (float)smallAsteroidAtlas.height / 2};
        break;
    default:
        puts("How'd you get here?");
        break;
    }

    return frameSize;
}

Vector2 ResourceHandler::getExplosionFrameSize(TextureSize size)
{
    Vector2 frameSize = Vector2{(float)largeExplosionAtlas.width / 9, (float)largeExplosionAtlas.height / 9};
    switch (size) {
    case LARGE:
        break;
    case MEDIUM:
        frameSize = Vector2{(float)mediumExplosionAtlas.width / 9, (float)mediumExplosionAtlas.height / 9};
        break;
    case SMALL:
        frameSize = Vector2{(float)smallExplosionAtlas.width / 9, (float)smallExplosionAtlas.height / 9};
        break;
    default:
        puts("How'd you get here?");
        break;
    }

    return frameSize;
}

Sound ResourceHandler::getSound(TextureSize size)
{
    Sound sound = largeAsteroidExplosion;
    switch (size) {
    case LARGE:
        break;
    case MEDIUM:
        sound = mediumAsteroidExplosion;
        break;
    case SMALL:
        sound = smallAsteroidExplosion;
        break;
    default:
        puts("How'd you get here?");
        break;
    }

    return sound;
}

void ResourceHandler::unload()
{
    UnloadTexture(ship);
    UnloadTexture(background);
    UnloadTexture(laser);
    UnloadTexture(heart);
    UnloadTexture(largeAsteroidAtlas);
    UnloadTexture(mediumAsteroidAtlas);
    UnloadTexture(smallAsteroidAtlas);
    UnloadTexture(largeExplosionAtlas);
    UnloadTexture(mediumExplosionAtlas);
    UnloadTexture(smallExplosionAtlas);
}