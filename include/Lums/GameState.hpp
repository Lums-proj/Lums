/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    GameState.hpp                                  oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_GAMESTATE_HPP
#define LUMS_GAMESTATE_HPP

#include <Lums/Event.hpp>
#include <Lums/ExportDll.hpp>

namespace lm
{
    /**
     * This class represents a GameState.
     * A GameState defines one state of your Game.
     * A state is a well-defined and encapsulated part of the game, such as
     * the Title screen, the game itself, a menu...
     * You should not use this class directly, instead, create your custom
     * gamestate that inherit from this base class.
     */
    class GameState
    {
    public:
        /**
         * GameState constructor.
         * You should not instanciate gamestates yourself.
         * Instead, use the factory methods Core::Push and Core::Transition.
         */
        LUMS_EXPORTED GameState();

        /**
         * Called when the GameState is loaded.
         * By default, do nothing.
         */
        LUMS_EXPORTED virtual void    load();

        /**
         * Called when the GameState is unloaded.
         * By default, do nothing.
         */
        LUMS_EXPORTED virtual void    unload();
        
        /**
         * Reload the State.
         * It's equivalent to a call to Unload, then a call to Load.
         */
        LUMS_EXPORTED void            reload();

        /**
         * Update the state.
         * This method is called on each physical tick.
         * You must overwrite this method.
         */
        virtual void    update() = 0;

        /**
         * Render the state.
         * This method is called when the state has to be redrawn.
         * You must overwrite this method.
         */
        virtual void    render() const = 0;

        /**
         * Process Events.
         * This method is called when a new event occurs.
         * You must overwrite this method.
         * @param event An event.
         */
        virtual void    handleEvent(const Event& event) = 0;

        /**
         * If this method return true, then Update() calls are forwarded
         * to the next state.
         * The default value is false.
         * @return True if updates are forwarded, false otherwise.
         */
        virtual bool
        forwardUpdate() const
        {
            return false;
        }

        /**
         * If this method return true, then Render() calls are forwarded
         * to the next state.
         * The default value is false.
         * @return True if renders are forwarded, false otherwise.
         */
        virtual bool
        forwardRender() const
        {
            return false;
        }

        /**
         * If this method return true, then HandleEvent() calls are forwarded
         * to the next state.
         * This method is called for each event.
         * The default value is false.
         * @param event The event to be forwarded.
         * @return True if events are forwarded, false otherwise.
         */
        virtual bool
        forwardEvent(const Event& event) const
        {
            return false;
        }

        /**
         * Remove this GameState from the Application stack.
         * After a call to this method, Unload() is called, the GameState
         * is removed from the stack, and is then deleted.
         * Deletion occurs immediately, so you must exit the gamestate scope
         * immediately after calling this method, else it's
         * undefined behavior.
         */
        LUMS_EXPORTED void        remove();

        /**
         * Destructor.
         */
        LUMS_EXPORTED virtual ~GameState();
    };
}

#endif