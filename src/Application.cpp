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
#include <NGL/GameState.h>

using namespace ngl;

Application::Application(int w, int h, std::string title)
: _running(false), _physicDelta(1 / 120), _renderDelta(1 / 60)
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
	SDL_Event	event;
	Uint32		lastUpdate;
	Uint32		lastRender;
	Uint32		now;

	_running = true;
	_deleteMark = true;
	StackRender();
	lastRender = SDL_GetTicks();
	lastUpdate = lastRender;
	while (_running)
	{
		if (_deleteMark)
		{
			_deleteMark = false;
			StackDelete();
		}
		now = SDL_GetTicks();
		if (now - lastUpdate > _physicDelta)
		{
			lastUpdate = now;
			while (SDL_PollEvent(&event))
				StackEvent(event);
			StackUpdate();
		}
		if (now - lastRender > _renderDelta)
		{
			lastRender = now;
			StackRender();
		}
		SDL_Delay(1);
	}
}

void			Application::Quit()
{
	_running = false;
}

void			Application::PushState(GameState *state)
{
	state->_app = this;
	_states.push_front(state);
}

void			Application::PopState()
{
	for (auto it = _states.begin(); it != _states.end(); ++it)
	{
		if ((*it)->_deleteMark == false)
		{
			(*it)->_deleteMark = true;
			_deleteMark = true;
			break;
		}
	}
}

void			Application::EmptyState()
{
	for (auto it = _states.begin(); it != _states.end(); ++it)
		(*it)->_deleteMark = true;
	_deleteMark = true;
}

Application::~Application()
{
	SDL_DestroyRenderer(_context.renderer);
	SDL_DestroyWindow(_context.window);
	_count--;
	if (_count == 0)
		SDL_Quit();
}

void			Application::Render(std::list<GameState*>::iterator it)
{
	GameState	*state;

	state = *it;
	if (state->ForwardRender() && std::next(it) != _states.end())
		Render(std::next(it));
	state->Render(_context);
}

void			Application::StackRender()
{
	SDL_SetRenderDrawColor(_context.renderer, 0, 0, 0, 255);
	SDL_RenderClear(_context.renderer);
	if (!_states.empty())
		Render(_states.begin());
	SDL_RenderPresent(_context.renderer);
}

void			Application::StackUpdate()
{
	auto		it = _states.begin();
	GameState*	state;

	while (it != _states.end())
	{
		state = *it;
		state->Update();
		if (!state->ForwardUpdate())
			break;
		++it;
	}
}

void			Application::StackEvent(SDL_Event &event)
{
	auto		it = _states.begin();
	GameState*	state;
	
	while (it != _states.end())
	{
		state = *it;
		state->Event(event);
		if (!state->ForwardEvent(event))
			break;
		++it;
	}
}

void			Application::StackDelete()
{
	GameState*	state;
	auto		it = _states.begin();

	while (it != _states.end())
	{
		state = *it;
		if (state->_deleteMark)
		{
			state->Unload();
			it = _states.erase(it);
			delete state;
		}
		else
			++it;
	}
}

int				Application::_count = 0;