#ifndef CUBE_H
#define CUBE_H

#include <Lums/Lums.h>

class Cube : public lm::GameState
{
public:
    Cube(lm::Core*);
    void    Load();
    void    Update();
    void    HandleEvent(const lm::Event& event);
    void    Render();
    void    Unload();
    
private:
    lm::Vector2a    angle;
    lm::Vector2f    speed;
};

#endif
