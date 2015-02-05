#include <Lums/AnimatedSprite.hpp>
#include <Lums/GL.hpp>

using namespace lm;

AnimatedSprite::AnimatedSprite()
: _animation(nullptr)
, _width(0)
, _height(0)
, _state(0)
, _baseState(0)
, _length(1)
, _acc(0)
, _speed(0)
{

}

AnimatedSprite::AnimatedSprite(Animation& animation)
: AnimatedSprite(animation, animation.width(), animation.height())
{

}

AnimatedSprite::AnimatedSprite(Animation& animation, int w, int h)
: AnimatedSprite()
{
	_animation = &animation;
	_width = w;
	_height = h;
}

void
AnimatedSprite::setAnimation(Animation& animation)
{
	setAnimation(animation, animation.width(), animation.height());
}

void
AnimatedSprite::setAnimation(Animation& animation, int w, int h)
{
	_animation = &animation;
	_width = w;
	_height = h;
}


void
AnimatedSprite::setState(size_t state, size_t length)
{
	_state = state;
	_baseState = state;
	_length = length;
	_acc = 0;
}

void
AnimatedSprite::setSpeed(size_t speed)
{
	_speed = speed;
	_acc = 0;
}

void
AnimatedSprite::update()
{
	_acc++;
	if (_acc >= _speed)
	{
		_acc = 0;
		_state++;
		if (_state >= _baseState + _length)
			_state = _baseState;
	}
}

void
AnimatedSprite::draw(int x, int y) const
{
	GLdouble nx = x;
	GLdouble ny = y;
	GLdouble w = static_cast<GLdouble>(_animation->width()) / _animation->image().width();
	GLdouble h = static_cast<GLdouble>(_animation->height()) / _animation->image().height();
	GLdouble tx = static_cast<GLdouble>(_state % _animation->wcount()) * w;
	GLdouble ty = static_cast<GLdouble>(_state / _animation->wcount()) * h;
	
	GLdouble arr[] = {
		nx, ny,
		tx, ty,
		nx + _width, ny,
		tx + w, ty,
		nx + _width, ny + _height,
		tx + w, ty + h,
		nx, ny + _height,
		tx, ty + h
	};

	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	_animation->image().bind();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_DOUBLE, 4 * sizeof(GLdouble), arr);
	glTexCoordPointer(2, GL_DOUBLE, 4 * sizeof(GLdouble), arr + 2);
	glDrawArrays(GL_QUADS, 0, 16);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopAttrib();
}
