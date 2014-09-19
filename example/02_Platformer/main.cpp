#include "Game.h"

using namespace lm;

int main()
{
    CoreGL  gl(800, 600, "Platformer");
    
    gl.Push(new Game);
    gl.Start();
}