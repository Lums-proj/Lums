#ifndef MAP_H
#define MAP_H

#include <Lums/Lums.h>
#include <vector>
#include "Player.h"

class Map
{
public:
    Map();
    void    Load();
    void    LoadNext();
    void    Spawn(Player& player);
    void    ResolveCollision(Player& player);
    void    ResolveCollision(Player& player, int x, int y);
    void    Render();

private:
    char    GetTile(int x, int y);
    int                 _index;
    std::vector<GLint>  _gfx;
    lm::Vector2i        _spawn;
};

#endif
