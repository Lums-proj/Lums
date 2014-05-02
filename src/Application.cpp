/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    Application.cpp                     :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#include <NGL/Application.h>

using namespace ngl;

Application::Application(int w, int h, std::string title)
: _running(false), _physicDelta(1.0f / 120.0f)
{
	_context.w = w;
	_context.h = h;
	_count++;
	if (_count == 1)
		SDL_Init(SDL_INIT_EVERYTHING);
	_context.window = SDL_CreateWindow(title.c_str(), 0, 0, w, h, 0);
	_context.renderer = SDL_CreateRenderer(_context.window,
										   -1,
										   SDL_RENDERER_ACCELERATED);
}

SDL_Window*		Application::Window() const
{
	return _context.window;
}

SDL_Renderer*	Application::Renderer() const
{
	return _context.renderer;
}

void			Application::SetWindowSize(int w, int h)
{
	_context.w = w;
	_context.h = h;
	SDL_SetWindowSize(_context.window, w, h);
}

void			Application::SetTitle(std::string title)
{
	SDL_SetWindowTitle(_context.window, title.c_str());
}

void			Application::Run()
{
	_running = true;
	SDL_Event	e;

	while (_running)
	{
		while (SDL_PollEvent(&e))
			;
	}
}

void			Application::Quit()
{
	_running = false;
}

Application::~Application()
{
	SDL_DestroyRenderer(_context.renderer);
	SDL_DestroyWindow(_context.window);
	_count--;
	if (_count == 0)
		SDL_Quit();
}

int				Application::_count = 0;