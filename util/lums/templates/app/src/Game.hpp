#ifndef GAME_HPP
#define GAME_HPP

#include <Lums>

class Game : public lm::GameState
{
public:
    Game();
    void    load();
    void    handleEvent(const lm::Event& event);
    void    update();
    void    render();
    void    unload();
    ~Game();

private:

};

#endif
