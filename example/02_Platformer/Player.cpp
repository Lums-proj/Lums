#include "Player.h"

using namespace lm;

static const GLint model[] =  {  0, 0,
                                10, 0,
                                10, 15,
                                 0, 15 };

Player::Player() : _pos(0.f, 0.f), _velocity(0, -0.15), _left(false), _right(false)
{
    
}

void Player::SetSpawn(int x, int y)
{
    _pos.x = x + 0.25f;
    _pos.y = y;
}

void    Player::Render()
{
    glLoadIdentity();
    glTranslatef(_pos.x * 20, _pos.y * 20, 0);
    glColor3f(1, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, 0, model);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void    Player::Update()
{
    if (_left)
        _velocity.x -= 0.1f;
    if (_right)
        _velocity.x += 0.1f;
    _pos += _velocity;
    _velocity.y += 0.01f;
    _velocity.x *= 0.5f;
}