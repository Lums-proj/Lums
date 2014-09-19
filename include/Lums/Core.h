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
#include <chrono>
#include <thread>
#include <iostream>

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
            _stack.push_front(state);
            state->Load();
        }

        /**
         * Pop the topmost State.
         * If there is no state, it's undefined behavior.
         */
        void        Pop()
        {
            State*  st;

            // Check if the actual state is the removed one.
            if (_it == _stack.begin())
            {
                ++_it;
                _jmp = true;
            }
            st = _stack.front();
            _stack.pop_front();
            st->Unload();
            delete st;
        }

        /**
         * Remove a state from the internal stack.
         * If the state does not exist within the internal stack, it's
         * undefined behavior.
         * @param state The state to be removed
         */
        void        Remove(State* state)
        {
            // If the state going to be removed is the active one,
            // then we should handle it by modifying the iterator.
            if (state == &*_it)
            {
                _it = _stack.erase(_it);
                _jmp = true;
            }
            else if (state->_core)
                _stack.remove(state);
            state->Unload();
            delete state;
        }

        /**
         * Clear the internal stack, and delete every element.
         */
        void        Clear()
        {
            while (!Stateless())
                Pop();
        }

        /**
         * Do a transition.
         * @param state The new state.
         */
        void        Transition(State* state)
        {
            Clear();
            Push(state);
        }
        
        /**
         * Check if the core is stateless.
         * @return True if the core is stateless
         */
        bool        Stateless() const
        {
            return _stack.empty();
        }

        ~Core() {};
    
    protected:
        typedef typename std::remove_reference<Event>::type EventStorage;
        
        T&              Impl()
        {
            return static_cast<T&>(*this);
        }
        
        EventStorage    _event;

    private:
        typedef std::list<State*>   Stack;

        void        DoEvent()
        {
            State*  st;
            bool    c;

            while (Impl().PollEvent())
            {
                for (_it = _stack.begin(); _it != _stack.end();)
                {
                    _jmp = false;
                    st = *_it;
                    c = st->ForwardEvent(_event);
                    st->HandleEvent(_event);
                    if (_jmp)
                        continue;
                    else
                        ++_it;
                }
            }
        }
        
        void        DoUpdate()
        {
            State*  st;
            bool    c;

            for (_it = _stack.begin(); _it != _stack.end();)
            {
                _jmp = false;
                st = *_it;
                c = st->ForwardUpdate();
                st->Update();
                if (_jmp)
                    continue;
                else
                    ++_it;
            }
        }
        
        void        DoRender()
        {
            auto    it = _stack.begin();
            auto    it_beg = it;
            auto    it_end = --(_stack.end());

            Impl().ClearScreen();
            while (it != it_end)
            {
                if (!(*it)->ForwardRender())
                    break;
                ++it;
            }
            while (true)
            {
                (*it)->Render();
                if (it == it_beg)
                    break;
                --it;
            }
            Impl().RefreshScreen();
        }

        Stack                                   _stack;
        typename Stack::iterator                _it;
        bool                                    _jmp;
        bool                                    _running;
    };
}

#endif