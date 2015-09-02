/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    ShaderProgram.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SHADER_PROGRAM_HPP
#define LUMS_SHADER_PROGRAM_HPP

#include <vector>
#include <LumsInclude/Graphics/OpenGL.hpp>
#include <LumsInclude/Math/Matrix.hpp>
#include <LumsInclude/Binary/BObject.hpp>

namespace lm
{
	class Shader;

	/**
     * @brief A class representing a linked shader
     */
	class ShaderProgram
	{
	public:
		/**
		 * Construct a shader program
		 */
		ShaderProgram();

		/**
		 * Get the raw shader program
		 * @return The raw shader program
		 */
		GLuint
		program() const
		{
			return _program;
		}

		/**
		 * Bind an attribute location inside the shader program
		 * @param index The index to be bound
		 * @param name The name of the attribute
		 */
		void
		bindAttribLocation(GLint index, const char* name) const
		{
			glBindAttribLocation(_program, index, name);
		}

		/**
		 * Attach a shader to the program
		 * @param shader The shader to attach
		 */
		void	attach(const Shader& shader);

		/**
		 * Link the shader
		 */
		void	link();

		/**
		 * Use the shader
		 */
		void	use() const;

        void    loadBinary(const BObject& object);

		/**
		 * Shader program dtor
		 */
		~ShaderProgram();

	private:
		GLuint				_program;
		std::vector<GLuint>	_shaders;

	};

	/**
	 * Set the value of an uniform
	 * @tparam T The type of the value
	 * @param program The shader
	 * @param name The uniform name
	 * @param value The value
	 */
	template <typename T>
    inline void
    uniform(ShaderProgram& program, const char* name, T& value)
    {
    	GLint loc = glGetUniformLocation(program.program(), name);
    	uniform(loc, value);
    }

    /**
	 * @cond
	 */
    inline void
    uniform(GLint loc, Matrix4f& mat)
    {
    	glUniformMatrix4fv(loc, 1, GL_FALSE, mat.data());
    }

    inline void
    uniform(GLint loc, float f)
    {
        glUniform1f(loc, f);
    }
    /**
     * @endcond
     */
}

#endif
