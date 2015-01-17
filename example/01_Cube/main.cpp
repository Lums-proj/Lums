/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    main.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.hpp"

using namespace lm;

int
main()
{
    Core gl(800, 600, "Cube");

    gl.push<Cube>();
    gl.start();
}