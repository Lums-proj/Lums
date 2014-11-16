/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Core.cpp                                     &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/Core.h>
#include <Lums/GL.h>
#include <SDL2/SDL_image.h>

using namespace lm;

Core::Core(int w, int h, const char* name, bool fullscreen)
: _it(0), _width(w), _height(h)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    _win = SDL_CreateWindow(name,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            w,
                            h,
                            SDL_WINDOW_OPENGL | (fullscreen
                                                 ? SDL_WINDOW_FULLSCREEN
                                                 : 0));
    _glcontext = SDL_GL_CreateContext(_win);
    glClearColor(0, 0, 0, 1);
}

void
Core::Start()
{
    // The renderer created time, and we must consume this time
    // in discrete chunks. That allow us to run the game
    // at max FPS : unlimited when there is no VSync, or
    // 60 on an 60Hz monitor...
    // Ticks are still fixed, so we get the best of both worlds
    
    using namespace std::chrono;
    
    // We avoid using floating point for performance reasons, so
    // we store time as nanoseconds.
    
    typedef unsigned long long      ns;
    typedef high_resolution_clock   localClock;
    typedef localClock::time_point  localTime;
    
    constexpr const ns  delta = 10000000; // 10ms as ns
    ns                  acc = 0;
    ns                  frameDuration;
    localTime           currentTime = localClock::now();
    localTime           newTime;
    
    _running = true;
    while (_running)
    {
        newTime = localClock::now();
        frameDuration = duration_cast<nanoseconds>(newTime - currentTime).count();
        currentTime = newTime;
        
        acc += frameDuration;
        while (acc >= delta)
        {
            acc -= delta;
            DoEvent();
            DoUpdate();
        }
        DoRender();
        std::this_thread::sleep_for(microseconds(400)); // CPU is happy
    }
}

void
Core::Pop()
{
    if (_stack.empty())
        return;
    if (_it)
        _it--;
    else
        _jmp = true;
    _stack.front()->Unload();
    _stack.erase(_stack.begin());
}

void
Core::Remove(GameState* state)
{
    long idx = std::find_if(_stack.begin(), _stack.end(), [&](std::unique_ptr<GameState>& p){ return p.get() == state; }) - _stack.begin();
    
    if (idx == _stack.size())
        return;
    if (idx == _it)
        _jmp = true;
    else if (idx < _it)
        _it--;
    _stack[idx]->Unload();
    _stack.erase(_stack.begin() + idx);
}

void
Core::Clear()
{
    while (!Stateless())
        Pop();
}

bool
Core::Stateless() const
{
    return _stack.empty();
}

void
Core::Stop()
{
    _running = false;
}


Core::~Core()
{
    SDL_GL_DeleteContext(_glcontext);
    SDL_DestroyWindow(_win);
    SDL_Quit();
    IMG_Quit();
}


// PRIVATE


void
Core::DoEvent()
{
    GameState*  st;
    Event       event;
    bool        c;
    
    while (SDL_PollEvent(&event))
    {
        for (_it = 0; _it < _stack.size(); _it++)
        {
        redo:
            _jmp = false;
            st = _stack[_it].get();
            c = st->ForwardEvent(event);
            st->HandleEvent(event);
            if (_jmp)
                goto redo;
        }
    }
}

void
Core::DoUpdate()
{
    GameState*  st;
    bool        c;
    
    for (_it = 0; _it < _stack.size(); _it++)
    {
    redo:
        _jmp = false;
        st = _stack[_it].get();
        c = st->ForwardUpdate();
        st->Update();
        if (_jmp)
            goto redo;
    }
}

void
Core::DoRender()
{
    int     min;

    for (min = 0; min < _stack.size() - 1; min++)
    {
        if (!_stack[min]->ForwardRender())
            break;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    while (min >= 0)
        _stack[min--]->Render();
    SDL_GL_SwapWindow(_win);
}
