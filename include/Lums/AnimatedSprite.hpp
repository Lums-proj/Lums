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

namespace lm
{
	class AnimatedSprite
	{
	public:
		AnimatedSprite();
		AnimatedSprite(Animation& animation);
		AnimatedSprite(Animation& animation, int w, int h);
		void	setAnimation(Animation& animation);
		void	setAnimation(Animation& animation, int w, int h);
		void	setState(size_t state, size_t length = 1);
		void	setSpeed(size_t speed);
		void	update();
		void	draw(int x = 0, int y = 0) const;


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