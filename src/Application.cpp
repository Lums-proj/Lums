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

#include <iostream>
#include <chrono>
#include <thread>
#include <NGL/Application.h>
#include <NGL/GameState.h>

using namespace ngl;
using namespace std::chrono;

Application::Application(int w, int h, std::string title)
: _running(false), _physicDelta(1.0f / 120.0f)
, _renderDelta(1.0f / 60.0f)
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
	SDL_Event							event;
	float								updateAcc;
	float								renderAcc;
	float								dt;
	high_resolution_clock::time_point	now;

	_running = true;
	_deleteMark = true;
	for (auto state : _states)
		state->Load();
	StackRender();
	now = high_resolution_clock::now();
	updateAcc = renderAcc = 0.0f;
	while (_running)
	{
		dt = duration_cast<duration<float>>(high_resolution_clock::now() - now).count();
		now = high_resolution_clock::now();
		updateAcc += dt;
		renderAcc += dt;
		if (_deleteMark)
		{
			_deleteMark = false;
			StackDelete();
		}
		while (SDL_PollEvent(&event))
			StackEvent(event);
		if (updateAcc > _physicDelta)
		{
			updateAcc -= _physicDelta;
			StackUpdate();
		}
		if (renderAcc > _renderDelta)
		{
			renderAcc -= _renderDelta;
			StackRender();
		}
		std::this_thread::sleep_for(microseconds(1000));
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
	if (_running)
		state->Load();
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