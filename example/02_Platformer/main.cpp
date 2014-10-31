#include "Game.h"

using namespace lm;

/*
 * This example is broken
 * TODO : Make it work
 */

int main()
{
    Core  gl(800, 600, "Platformer");
    
    gl.Push<Game>();
    gl.Start();
}