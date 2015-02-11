/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    AnimatedSprite.hpp                             oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_ANIMATEDSPRITE_HPP
#define LUMS_ANIMATEDSPRITE_HPP

#include <Lums/Animation.hpp>
#include <Lums/ExportDll.hpp>

namespace lm
{
	class AnimatedSprite
	{
	public:
		LUMS_EXPORTED AnimatedSprite();
		LUMS_EXPORTED AnimatedSprite(Animation& animation);
		LUMS_EXPORTED AnimatedSprite(Animation& animation, int w, int h);
		LUMS_EXPORTED void	setAnimation(Animation& animation);
		LUMS_EXPORTED void	setAnimation(Animation& animation, int w, int h);
		LUMS_EXPORTED void	setState(size_t state, size_t length = 1);
		LUMS_EXPORTED void	setSpeed(size_t speed);
		LUMS_EXPORTED void	update();
		LUMS_EXPORTED void	draw(int x = 0, int y = 0) const;


	private:
		Animation*	_animation;
		int			_width;
		int			_height;
		size_t		_state;
		size_t		_baseState;
		size_t		_length;
		size_t		_acc;
		size_t		_speed;
	};
}

#endif