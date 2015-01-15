#ifndef CUBE_H
#define CUBE_H

#include <Lums/Lums.h>

class Cube : public lm::GameState
{
public:
    Cube(lm::Core*);
    void    load();
    void    update();
    void    handleEvent(const lm::Event& event);
    void    render();
    void    unload();
    
private:
    lm::Vector2a    angle;
    lm::Vector2f    speed;
};

#endif
