/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    GameState.cpp                       :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#include <NGL/GameState.h>
#include <NGL/Application.h>

using namespace ngl;

Application&	GameState::App() const
{
	return *_app;
}

void			GameState::Close()
{
	_deleteMark = true;
	_app->_deleteMark = true;
}