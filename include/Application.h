/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    Application.h                       :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL2/SDL.h>
#include <NGL/RenderContext.h>
#include <string>

namespace ngl
{

/**
 * @class Application
 * This class defines an application.
 * An application is composed of a window, a renderer, a state machine and
 * a main loop.
 * The goal of this class is to provide a simple, yet efficient way to
 * handle the context of your game.
 */
class Application
{
public:
	/**
	 * Create an Application.
	 * @param w The width of the window.
	 * @param h The height of the window.
	 * @param title The window title.
	 */
	Application(int w, int h, std::string title = "");
	
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
	 * Destructor.
	 */
	~Application();
	
private:
	RenderContext	_context;
	bool			_running;
	double			_physicDelta;
	static int		_count;
};
	
}

#endif /* !APPLICATION_H */