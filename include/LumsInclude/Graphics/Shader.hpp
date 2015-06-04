/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Shader.hpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SHADER_HPP
#define LUMS_SHADER_HPP

#include <LumsInclude/Graphics/OpenGL.hpp>

namespace lm
{
	/**
	 * @brief A class representing a shader
	 */
	class Shader
	{
	friend class ShaderProgram;
	
	public:
		/**
		 * An enum defining the shader type
		 */
		enum Type
		{
			Vertex,
			Fragment
		};

		/**
		 * Construct a shader from it's type and path
		 * @param path The shader path
		 * @param type The shader type
		 * @param resource If true, path is relative to the resource path
		 */
		Shader(const char* path, Type type, bool resource = true);
		
		/**
		 * Get the raw shader
		 * @return The raw shader
		 */
		GLuint
		get() const
		{
			return _shader;
		}
		
		/**
		 * Shader dtor
		 */
		~Shader();

	private:
		Shader();
		void	load(const char* data, GLenum type);
		GLuint	_shader;
	};
}

#endif