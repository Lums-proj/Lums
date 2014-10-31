# Getting Started



## Basic program

Let's start with a minimal, working example.

We need to create a class to manage our game.  
Let's create Game.h

```c++
#include <Lums/Lums.h>

class Game : public lm::GameState
{
    Game(lm::Core* core)
    : lm::GameState(core)
    {

    }

    void
    Update()
    {

    }

    void
    Render()
    {

    }

    void
    HandleEvent(const Event& event)
    {
        if (event.type == SDL_KEYDOWN
            && event.key.keysym.sym == SDLK_ESCAPE)
            Core().Stop();
    }
};
```

Then we create a quick main.cpp file to test our class.

```c++
#include "Game.h"

int
main(void)
{
    lm::Core core(800, 600, "Our fantastic game!");

    core.Push<Game>();
    core.Start();
    return 0;
}
```

That's all. Build, launch, and you should see a 800x600 black window.  
Press esc, and the program exit. As simple as that.