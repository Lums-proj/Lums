#ifndef GAME_H
#define GAME_H

#include <vector>
#include <Lums/Lums.h>
#include "Player.h"
#include "Map.h"

class Game : public lm::GameState
{
public:
    Game(lm::Core* core);
    void    Load();
    void    Render();
    void    Update();
    void    HandleEvent(const lm::Event& event);
    
private:
    Player              _player;
    Map                 _map;
};

#endif