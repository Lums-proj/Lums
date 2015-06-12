/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    ShaderPipeline.cpp                             oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Graphics/ShaderPipeline.hpp>
#include <iostream>

using namespace lm;

ShaderPipeline::ShaderPipeline()
: _win(nullptr)
{
	_vbo.push(-1.f, -1.f, 0.f, 0.f);
	_vbo.push(1.f, -1.f, 1.f, 0.f);
	_vbo.push(1.f, 1.f, 1.f, 1.f);
	_vbo.push(-1.f, -1.f, 0.f, 0.f);
	_vbo.push(1.f, 1.f, 1.f, 1.f);
	_vbo.push(-1.f, 1.f, 0.f, 1.f);
	_vbo.send();
}

void
ShaderPipeline::setWindow(const Window& win)
{
	_win = &win;
}

void
ShaderPipeline::bind()
{
	if (!_shaders.empty())
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _win->fbo());
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT */);
	}
}

void
ShaderPipeline::append(const ShaderProgram& shader)
{
	_shaders.push_back(&shader);
}

void
ShaderPipeline::prepend(const ShaderProgram& shader)
{
	_shaders.push_front(&shader);
}

void
ShaderPipeline::clear()
{
	_shaders.clear();
}

void
ShaderPipeline::render()
{
	std::size_t max = _shaders.size();
	int in = 0;

	for (std::size_t i = 0; i < max; ++i)
	{
		_shaders[i]->use();
		glBindTexture(GL_TEXTURE_2D, _win->tex(in));
		if (i + 1 == max)
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		else
		{
			if (in)
				glDrawBuffer(GL_COLOR_ATTACHMENT0);
			else
				glDrawBuffer(GL_COLOR_ATTACHMENT1);
			glClear(GL_COLOR_BUFFER_BIT);
		}
		_vbo.draw(GL_TRIANGLES);
		in = 1 - in;
	}
}

ShaderPipeline::~ShaderPipeline()
{

}
