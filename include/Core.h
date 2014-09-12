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
#include <list>
#include <iterator>

namespace lm
{
    /**
     * An helper template to deduce types.
     */
    template <class T>
    struct CoreTraits;

    /**
     * This class defines a core.
     * A core is composed of a window, a renderer, a state machine and
     * a main loop.
     * The goal of this class is to provide a simple, yet efficient way to
     * handle the context of your game.
     */
    template <class T>
    class Core
    {
    public:
        Core() : _it(_stack.end()) {};

        typedef typename CoreTraits<T>::State    State;
        typedef typename CoreTraits<T>::Event    Event;

        /**
         * Start the core.
         */
        void        Start()
        {
            _running = true;
            while (_running)
            {
                // Do things
            }
        }

        /**
         * Stop the core
         */
        void        Stop()
        {
            _running = false;
        }
        
        /**
         * Push a new State.
         * @param state The new state.
         */
        void        Push(State* state)
        {
            state->_core = static_cast<T*>(this);
            state->Load();
            _stack.push_front(state);
        }
        
        /**
         * Push a new State.
         * @param state The new state.
         */
        void        Push(State& state)
        {
            Push(&state);
        }

        /**
         * Pop the topmost State.
         * If there is no state, it's undefined behavior.
         * @return The top state.
         */
        State&      Pop()
        {
            State*  st;

            // Check if the actual state is the removed one.
            if (_it == _stack.begin())
            {
                ++_it;
                _jmp = true;
            }
            st = _stack.pop_front();
            st->Unload();
        }
        
        /**
         * Pop and delete the topmost State.
         * If there is no state, it's undefined behavior.
         */
        void        Remove()
        {
            delete &Pop();
        }
        
        ~Core() {};
        
    private:
        
        bool                                    _running;
        std::list<State*>                       _stack;
        typename std::list<State*>::iterator    _it;
        bool                                    _jmp;
    };
}

#endif