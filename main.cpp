#include "src/game/Game.hpp"

int main()
{
    try
    {
        Qy::Game game;
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}