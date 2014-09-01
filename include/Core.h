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

#include <SDL2/SDL.h>
#include <string>
#include <list>
#include "RenderContext.h"

namespace lm
{
    class GameState;

    /**
     * This class defines a core.
     * A core is composed of a window, a renderer, a state machine and
     * a main loop.
     * The goal of this class is to provide a simple, yet efficient way to
     * handle the context of your game.
     */
    class Core
    {
    friend class GameState;
    public:
        /**
         * Create a Core.
         * @param w The width of the window.
         * @param h The height of the window.
         * @param title The window title.
         */
        Core(int w, int h, std::string title = "");

        /**
         * Get the application window.
         * @return The application window, or nullptr if not defined.
         */
        SDL_Window*		Window() const;

        /**
         * Get the application renderer.
         * @return The application renderer, or nullptr if not defined.
         */
        SDL_Renderer*	Renderer() const;

        /**
         * Set the window size.
         * @param w The width of the window.
         * @param h the height of the window.
         */
        void			SetWindowSize(int w, int h);

        /**
         * Set the window title.
         * @param title The window's new title.
         */
        void			SetTitle(std::string title);

        /**
         * Run the application.
         * This function return once a call to Quit() has been made.
         */
        void			Run();

        /**
         * Quit the application.
         */
        void			Quit();

        /**
         * Push a state on the state stack.
         * @param state The state to be pushed.
         */
        void			PushState(GameState* state);

        /**
         * Pop a state from the state stack.
         */
        void			PopState();

        /**
         * Empty the state stack.
         */
        void			EmptyState();

        /**
         * Replace the stack state with a single state.
         * This is equivalent to calling EmptyState() and PushState().
         * @param state A state.
         */
        void			SetState(GameState* state)
        {
            EmptyState();
            PushState(state);
        };

        /**
         * Destructor.
         */
        ~Core();

    private:
        void					Render(std::list<GameState*>::iterator it);
        void					StackRender();
        void					StackUpdate();
        void					StackEvent(SDL_Event& event);
        void					StackDelete();
        RenderContext			_context;
        bool					_running;
        float					_physicDelta;
        float					_renderDelta;
        static int				_count;
        std::list<GameState*>	_states;
        bool					_deleteMark;
    };
}

#endif