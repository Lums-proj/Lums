#include "Map.h"

using namespace lm;

static const char   map[] =         "########################################"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#       S                              #"
                                    "#     #####                            #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "#                                      #"
                                    "########################################";

Map::Map() : _index(0)
{
    Load();
}

void Map::Load()
{
    _gfx.clear();
    for (int i = _index * 1200; i < 1200 + _index * 1200; i++)
    {
        int x = i % 40;
        int y = i / 40;
        
        switch (map[i])
        {
            case '#':
                _gfx.push_back(x * 20);
                _gfx.push_back(y * 20);
                _gfx.push_back((x + 1) * 20);
                _gfx.push_back(y * 20);
                _gfx.push_back((x + 1) * 20);
                _gfx.push_back((y + 1) * 20);
                _gfx.push_back(x * 20);
                _gfx.push_back((y + 1) * 20);
                break;
            case 'S':
                _spawn.Set(x, y);
                break;
        }
    }

    
}

void Map::LoadNext()
{
    _index++;
    Load();
}

void    Map::Spawn(Player& player)
{
    player.SetSpawn(_spawn.x, _spawn.y);
}

void    Map::ResolveCollision(Player &player)
{
    Vector2f    pos = player.Pos();

    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            ResolveCollision(player, pos.x + i, pos.y + j);
}

void    Map::ResolveCollision(Player &player, int x, int y)
{
    Vector2f    pos = player.Pos();
    Vector2f    size = player.Size();
    float       px;
    float       py;

    if (GetTile(x, y) != '#')
        return;
    if (pos.x > x + 1 || pos.y > y + 1 || pos.x + size.x < x || pos.y + size.y < y)
        return;
    px = std::min(std::abs(pos.x - (x + 1)), std::abs(pos.x + size.x - x));
    py = std::min(std::abs(pos.y - (y + 1)), std::abs(pos.y + size.y - y));
    if (py < px)
    {
        pos.y = player.Velocity().y > 0 ? y - size.y : y;
        player.Velocity().y = 0;
    }
    else
    {
        pos.x = player.Velocity().x > 0 ? x - size.x : x;
        player.Velocity().x = 0;
    }
    player.Move(pos);
}

void    Map::Render()
{
    glColor3f(1, 1, 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, 0, &(_gfx[0]));
    glDrawArrays(GL_QUADS, 0, (int)_gfx.size() / 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

char    Map::GetTile(int x, int y)
{
    if (x < 0 || x >= 40 || y < 0 || y >= 30)
        return '#';
    return map[1200 * _index + 40 * y + x];
}