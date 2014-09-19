#include "Cube.h"

using namespace lm;

int main()
{
    CoreGL  gl(800, 600, "Cube");

    gl.Push(new Cube);
    gl.Start();
}