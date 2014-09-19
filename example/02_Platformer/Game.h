#ifndef GAME_H
#define GAME_H

#include <vector>
#include <Lums/Lums.h>
#include "Player.h"
#include "Map.h"

class Game : public lm::GameStateGL
{
public:
    void    Load();
    void    Render();
    void    Update();
    void    HandleEvent(SDL_Event& event);
    
private:
    Player              _player;
    Map                 _map;
};

#endif