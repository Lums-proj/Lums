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

namespace lm
{
	class Shader;

	class ShaderProgram
	{
	public:
		ShaderProgram();

		GLuint
		program() const
		{
			return _program;
		}

		void
		bindAttribLocation(GLint index, const char* name) const
		{
			glBindAttribLocation(_program, index, name);
		}

		void	attach(const Shader& shader);
		void	link();
		void	use() const;
		~ShaderProgram();

	private:
		GLuint				_program;
		std::vector<GLuint>	_shaders;

	};

	template <typename T>
    inline void
    uniform(ShaderProgram& program, const char* name, T& value)
    {
    	GLint loc = glGetUniformLocation(program.program(), name);
    	uniform(loc, value);
    }

    inline void
    uniform(GLint loc, Matrix4f& mat)
    {
    	glUniformMatrix4fv(loc, 1, GL_FALSE, mat.data());
    }
}

#endif
