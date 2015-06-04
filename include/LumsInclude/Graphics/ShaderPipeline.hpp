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
	/**
	 * @brief A class describing a chain of shaders
	 *
	 * This class implements something known as ping-pong rendering.
	 */
	class ShaderPipeline
	{
	public:
		/**
		 * Create a shader pipeline
		 */
		ShaderPipeline();

		/**
		 * Set the shader pipeline active window
		 * @param win A reference to a window
		 */
		void	setWindow(const Window& win);

		/**
		 * Bind the pipeline.
		 * You should call this function before rendering
		 */
		void	bind();

		/**
		 * Append a shader to the pipeline
		 * @param shader The shader to append
		 */
		void	append(const ShaderProgram& shader);

		/**
		 * Prepend a shader to the pipeline
		 * @param shader The shader to prepend
		 */
		void	prepend(const ShaderProgram& shader);

		/**
		 * Remove every shader from the pipeline
		 */
		void	clear();

		/**
		 * Render the pipeline to screen
		 */
		void	render();

		/**
		 * Shader pipeline dtor
		 */
		~ShaderPipeline();

	private:
		const Window*											_win;
		std::deque<const ShaderProgram*>						_shaders;
		VertexBuffer<Vertex::Position, 2, Vertex::Texture, 2>	_vbo;
	};
}

#endif
