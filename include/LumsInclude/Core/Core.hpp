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
#include <LumsInclude/Graphics/Window.hpp>
#include <LumsInclude/Core/GameState.hpp>
#include <LumsInclude/ExportDll.hpp>

namespace lm
{
    /**
     * @brief This class defines a core
     *
     * A core is composed of a window, a renderer, a state machine and
     * a main loop.
     * The goal of this class is to provide a simple, yet efficient way to
     * handle the context of your game.
     */
    class Core : public Singleton<Core>
    {
    public:
        friend class Singleton<Core>;

        /**
         * Get the window linked to the core.
         * It's undefined behavior to call this method when
         * no window is attached.
         * @return A reference to the linked window
         */
        Window&
        window()
        {
            return *_win;
        }

        /**
         * Set the linked window
         * @param win A pointer to a window
         */
        void
        setWindow(Window* win)
        {
            delete _win;
            _win = win;
        }

        /**
         * Start the core.
         * This method will not return until Core::Stop
         * have been called.
         */
        LUMS_EXPORTED void    start();
        
        /**
         * Stop the core.
         */
        LUMS_EXPORTED void    stop();
        
        /**
         * Push a new State.
         * @tparam T The class to be instanciated. Must inherit GameState.
         * @tparam Args Argument types.
         * @param args Argument instances.
         * @return A reference to the constructed object.
         */
        template<typename T, typename ...Args>
        T&
        push(Args ...args)
        {
            using namespace std::chrono;
    
            typedef high_resolution_clock   localClock;
            typedef localClock::time_point  localTime;

            localTime beforeLoad = localClock::now();

            T* state = new T(std::forward<Args>(args)...);
            _stack.insert(_stack.begin(), std::unique_ptr<GameState>(state));
            state->load();

            localTime afterLoad = localClock::now();
            _lagTime += duration_cast<nanoseconds>(afterLoad - beforeLoad).count();
            return *state;
        }
        
        /**
         * Pop the topmost State.
         * If there is no state, it's a no-op.
         */
        LUMS_EXPORTED void    pop();
        
        /**
         * Remove a state from the internal stack.
         * If the state does not exist within the internal stack,
         * it's a no-op.
         * @param state The state to be removed
         */
        LUMS_EXPORTED void    remove(GameState* state);
        
        /**
         * Clear the internal stack, and delete every element.
         */
        LUMS_EXPORTED void    clear();
        
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
        LUMS_EXPORTED bool    stateless() const;
        
        /**
         * Core dtor
         */
        LUMS_EXPORTED ~Core();
        
    private:
        LUMS_EXPORTED Core();
        
        void    doEvent();
        void    doUpdate();
        void    doRender();
        
        typedef std::vector<std::unique_ptr<GameState>> Stack;
        
        Stack               _stack;
        size_t              _it;
        Window*             _win;
        bool                _jmp;
        bool                _running;
        long long           _lagTime;
    };
}

#endif