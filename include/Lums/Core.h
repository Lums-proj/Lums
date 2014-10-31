/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Core.h                                       &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_CORE_H
#define LUMS_CORE_H

#include <string>
#include <vector>
#include <iterator>
#include <chrono>
#include <thread>
#include <memory>
#include <SDL2/SDL.h>
#include <Lums/GameState.h>

namespace lm
{
    /**
     * This class defines a core.
     * A core is composed of a window, a renderer, a state machine and
     * a main loop.
     * The goal of this class is to provide a simple, yet efficient way to
     * handle the context of your game.
     */
    class Core
    {
    public:
        /**
         * Create a new Core.
         * @param w The width of the core window.
         * @param h The height of the core window.
         * @param name The window title.
         * @param fullscreen Wether to start the core fullscreen.
         */
        Core(int w, int h, const char* name = "", bool fullscreen = false);
        
        /**
         * Return the window width.
         * @return The window width.
         */
        int
        Width() const
        {
            return _width;
        }
        
        /**
         * Return the window height.
         * @return The window height.
         */
        int
        Height() const
        {
            return _height;
        }
        
        /**
         * Start the core.
         * This method will not return until Core::Stop
         * have been called.
         */
        void    Start();
        
        /**
         * Stop the core.
         */
        void    Stop();
        
        /**
         * Push a new State.
         * @tparam T The class to be instanciated. Must inherit GameState.
         * @tparam Args Argument types.
         * @param args Argument instances.
         * @return A reference to the constructed object.
         */
        template<typename T, typename ...Args> T&
        Push(Args ...args)
        {
            T* state = new T(this, std::forward<Args>(args)...);
            _stack.insert(_stack.begin(), std::unique_ptr<GameState>(state));
            state->Load();
            return *state;
        }
        
        /**
         * Pop the topmost State.
         * If there is no state, it's a no-op.
         */
        void    Pop();
        
        /**
         * Remove a state from the internal stack.
         * If the state does not exist within the internal stack,
         * it's a no-op.
         * @param state The state to be removed
         */
        void    Remove(GameState* state);
        
        /**
         * Clear the internal stack, and delete every element.
         */
        void    Clear();
        
        /**
         * Do a transition.
         * This method clear the stack, then push a new GameState.
         * @tparam T A class to be instanciated.
         * @tparam Args Argument types.
         * @param args Argument instances.
         * @return A reference to the constructed object.
         */
        template<typename T, typename ...Args> T&
        Transition(Args ...args)
        {
            Clear();
            return Push<T>(args...);
        }
        
        /**
         * Check if the core is stateless.
         * @return True if the core is stateless
         */
        bool    Stateless() const;
        
        ~Core();
        
    private:
        void    DoEvent();
        void    DoUpdate();
        void    DoRender();
        
        typedef std::vector<std::unique_ptr<GameState>> Stack;
        
        Stack           _stack;
        int             _it;
        int             _width;
        int             _height;
        SDL_Window*     _win;
        SDL_GLContext   _glcontext;
        bool            _jmp;
        bool            _running;
    };
}

#endif