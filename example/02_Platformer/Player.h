#ifndef PLAYER_H
#define PLAYER_H

#include <Lums/Lums.h>

class Player
{
public:
    Player();
    const lm::Vector2f     Pos() const
    {
        return _pos;
    }
    const lm::Vector2f     Size() const
    {
        return lm::Vector2f(0.5f, 0.75f);
    }
    lm::Vector2f&      Velocity()
    {
        return _velocity;
    }
    void                    Move(lm::Vector2f pos)
    {
        _pos = pos;
    }
    void                    Left(bool b)
    {
        _left = b;
    }
    void                    Right(bool b)
    {
        _right = b;
    }
    void                    SetSpawn(int x, int y);
    void                    Render();
    void                    Update();

private:
    lm::Vector2f            _pos;
    lm::Vector2f            _velocity;
    bool                    _left;
    bool                    _right;
};

#endif
