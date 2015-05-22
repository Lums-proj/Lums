/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    ShaderPipeline.hpp                             oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SHADER_PIPELINE_HPP
#define LUMS_SHADER_PIPELINE_HPP

#include <deque>
#include <LumsInclude/Graphics/ShaderProgram.hpp>
#include <LumsInclude/Graphics/VertexBuffer.hpp>
#include <LumsInclude/Graphics/Window.hpp>

namespace lm
{
	class ShaderPipeline
	{
	public:
		ShaderPipeline();
		void	setWindow(const Window& win);
		void	bind();
		void	append(const ShaderProgram& shader);
		void	prepend(const ShaderProgram& shader);
		void	clear();
		void	render();
		~ShaderPipeline();

	private:
		const Window*											_win;
		std::deque<const ShaderProgram*>						_shaders;
		VertexBuffer<Vertex::Position, 2, Vertex::Texture, 2>	_vbo;
	};
}

#endif
