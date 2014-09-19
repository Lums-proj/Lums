#ifndef CUBE_H
#define CUBE_H

#include <Lums/Lums.h>

class Cube : public lm::GameStateGL
{
public:
    Cube();
    void            Load();
    void            Update();
    void            HandleEvent(SDL_Event& event);
    void            Render();
    void            Unload();
    
private:
    lm::Vector2a    angle;
    lm::Vector2f    speed;
};

#endif
