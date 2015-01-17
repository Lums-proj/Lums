/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Core.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_CORE_HPP
#define LUMS_CORE_HPP

#include <string>
#include <vector>
#include <iterator>
#include <chrono>
#include <thread>
#include <memory>
#include <Lums/Window.hpp>
#include <Lums/GameState.hpp>

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
         * If a Core was already created, and has not been destructed, it's
         * undefined behavior.
         * @param w The width of the core window.
         * @param h The height of the core window.
         * @param name The window title.
         * @param fullscreen Wether to start the core fullscreen.
         */
        Core(int w, int h, const char* name = "", bool fullscreen = false);

        /**
        * Get the Core singleton.
        * If there is no singleton Core, this is undefined behavior.
        * @return A reference to the singleton Core
        */        
        static Core&
        get()
        {
            return *_singleton;
        }

        /**
         * Return the window width.
         * @return The window width.
         */
        int
        width() const
        {
            return _width;
        }
        
        /**
         * Return the window height.
         * @return The window height.
         */
        int
        height() const
        {
            return _height;
        }
        
        /**
         * Start the core.
         * This method will not return until Core::Stop
         * have been called.
         */
        void    start();
        
        /**
         * Stop the core.
         */
        void    stop();
        
        /**
         * Push a new State.
         * @tparam T The class to be instanciated. Must inherit GameState.
         * @tparam Args Argument types.
         * @param args Argument instances.
         * @return A reference to the constructed object.
         */
        template<typename T, typename ...Args> T&
        push(Args ...args)
        {
            T* state = new T(std::forward<Args>(args)...);
            _stack.insert(_stack.begin(), std::unique_ptr<GameState>(state));
            state->load();
            return *state;
        }
        
        /**
         * Pop the topmost State.
         * If there is no state, it's a no-op.
         */
        void    pop();
        
        /**
         * Remove a state from the internal stack.
         * If the state does not exist within the internal stack,
         * it's a no-op.
         * @param state The state to be removed
         */
        void    remove(GameState* state);
        
        /**
         * Clear the internal stack, and delete every element.
         */
        void    clear();
        
        /**
         * Do a transition.
         * This method clear the stack, then push a new GameState.
         * @tparam T A class to be instanciated.
         * @tparam Args Argument types.
         * @param args Argument instances.
         * @return A reference to the constructed object.
         */
        template<typename T, typename ...Args> T&
        transition(Args ...args)
        {
            clear();
            return push<T>(args...);
        }
        
        /**
         * Check if the core is stateless.
         * @return True if the core is stateless
         */
        bool    stateless() const;
        
        ~Core();
        
    private:
        void    doEvent();
        void    doUpdate();
        void    doRender();
        
        typedef std::vector<std::unique_ptr<GameState>> Stack;
        
        Stack           _stack;
        int             _it;
        int             _width;
        int             _height;
        Window          _win;
        bool            _jmp;
        bool            _running;
        static Core*    _singleton;
    };
}

#endif