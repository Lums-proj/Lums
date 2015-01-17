/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Cube.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_HPP
#define CUBE_HPP

#include <Lums/Lums.hpp>

class Cube : public lm::GameState
{
public:
    Cube();
    void    load();
    void    update();
    void    handleEvent(const lm::Event& event);
    void    render() const;
    void    unload();
    
private:
    lm::Vector2a    angle;
    lm::Vector2f    speed;
};

#endif
