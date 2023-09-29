#ifndef GLOBALS_HPP
#define GLOBALS_HPP

enum class GameState
{
    PAUSED,
    RUNNING,
    GAME_OVER
};

namespace Globals
{
    inline bool DEBUG_MODE = false;
}

#endif // !GLOBALS_HPP
#define GLOBALS_HPP