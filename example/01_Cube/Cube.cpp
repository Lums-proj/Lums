#include "Cube.h"
#include <iostream>

using namespace lm;

const GLfloat   vertices[] = {
     1,  1,  1,
     1,  1, -1,
     1, -1,  1,
    -1,  1,  1,
     1, -1, -1,
    -1,  1, -1,
    -1, -1,  1,
    -1, -1, -1
};

const GLfloat   colors[] = {
    1, 0, 0,
    0, 1, 0,
    0, 0, 1,
    1, 1, 0,
    1, 0, 1,
    0, 1, 1,
    1, 0, 1,
    1, 1, 1
};

const GLubyte   indices[] = {
    0, 2, 6, 3,
    3, 5, 7, 6,
    5, 1, 4, 7,
    1, 0, 2, 4,
    1, 0, 3, 5,
    2, 4, 7, 6
};

Cube::Cube(lm::Core* core) : lm::GameState(core), speed(10, 0)
{
    
}

void    Cube::Load()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPerspective(70, 1.333f, 0.001f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void    Cube::Update()
{
    angle.x += 0.1_deg * speed.x;
    angle.y += 0.1_deg * speed.y;
}

void    Cube::HandleEvent(const Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                Core().Stop();
                break;
            case SDLK_RIGHT:
                speed.x++;
                break;
            case SDLK_LEFT:
                speed.x--;
                break;
            case SDLK_UP:
                speed.y++;
                break;
            case SDLK_DOWN:
                speed.y--;
                break;
            default:
                break;
        }
    }
}

void    Cube::Render()
{
    glLookAt(-2, 2, -2, 0, 0, 0, 0, 1, 0);
    glRotatef(angle.x.toDegrees(), 0, 1, 0);
    glRotatef(angle.y.toDegrees(), 0, 0, 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}

void    Cube::Unload()
{
    glDisable(GL_DEPTH_TEST);
}