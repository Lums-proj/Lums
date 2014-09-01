/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    GameState.h                                  &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_GAMESTATE_H
#define LUMS_GAMESTATE_H

#include <SDL2/SDL.h>

namespace lm
{
    class Core;
    struct RenderContext;

    /**
     * @class GameState
     * This class represents a GameState.
     * A GameState defines one state of your Game.
     * A state is a well-defined and encapsulated part of the game, such as
     * the Title screen, the game itself, a menu...
     * You should not use this class directly, instead, create your custom
     * gamestate that inherit from this base class.
     */
    class GameState
    {
    friend class Core;
    public:
        /**
         * GameState constructor.
         * You should only alocate gamestates on the heap using new, not on
         * the stack.
         */
        GameState() : _core(nullptr), _deleteMark(false) {};

        /**
         * This method is called when the GameState is loaded.
         */
        virtual void		Load() {};

        /**
         * This method is called when the GameState is unloaded.
         */
        virtual void		Unload() {};

        /**
         * Get the core linked with this GameState.
         * Calling this method from the constructor is undefined behavior.
         * Instead, call this method from Load().
         * @return A reference to the Core linked with this state.
         */
        Core&               Core() const;

        /**
         * Update the state.
         * This method is called on each physical tick.
         */
        virtual void		Update() {};

        /**
         * Render the state.
         * This method is called when the state has to be redrawn.
         * @param context A rendering context.
         */
        virtual void		Render(RenderContext& context) {};

        /**
         * Process Events.
         * This method is called when a new event occurs.
         * @param event An SDL event.
         */
        virtual void		Event(SDL_Event& event) {};

        /**
         * If this method return true, then Update() calls are forwarded
         * to the next state.
         * @return True if updates are forwarded, false otherwise.
         * The default value is false.
         */
        virtual bool		ForwardUpdate() { return false; };

        /**
         * If this method return true, then Render() calls are forwarded
         * to the next state.
         * @return True if renders are forwarded, false otherwise.
         * The default value is false.
         */
        virtual bool		ForwardRender() { return false; };

        /**
         * If this method return true, then Event() calls are forwarded
         * to the next state.
         * This method is called for each event.
         * @param event The event to be forwarded.
         * @return True if events are forwarded, false otherwise.
         * The default value is false.
         */
        virtual bool		ForwardEvent(SDL_Event& event) { return false; };

        /**
         * Remove this GameState from the Application stack.
         * After a call to this method, Unload() is called, the GameState
         * is removed from the stack, and is then deleted.
         */
        void				Close();

        /**
         * Destructor.
         */
        virtual ~GameState() {};

    private:
        lm::Core*           _core;
        bool				_deleteMark;
    };
}

#endif