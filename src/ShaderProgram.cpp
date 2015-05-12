/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    ShaderProgram.cpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/ShaderProgram.hpp>
#include <Lums/Shader.hpp>
#include <iostream>

using namespace lm;

ShaderProgram::ShaderProgram()
{
	_program = glCreateProgram();
}

void
ShaderProgram::attach(const Shader& shader)
{
	const GLuint s = shader.get();

	glAttachShader(_program, s);
	_shaders.push_back(s);
}

void
ShaderProgram::link()
{
    GLint linked = 0;

	glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &linked);
    if (linked)
    {
	   for (auto s : _shaders)
		  glDetachShader(_program, s);
	   _shaders.clear();
    }
    else
    {
    	char* msg;
		GLint logSize;

		std::cout << "Link failed!" << std::endl;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logSize);
		msg = new char[logSize];
		glGetProgramInfoLog(_program, logSize, nullptr, msg);
		puts(msg);
		delete [] msg;
    }
}

void
ShaderProgram::use() const
{
	glUseProgram(_program);
}

const ShaderProgram&
ShaderProgram::defaultProgram()
{
	static ShaderProgram def;
	static bool init;

	if (!init)
	{
        /*
		Shader fragLink;
		Shader vertLink;

		const char* fragStr = ""
            "#version 150\n"
			"vec4 lm_fragColor();\n"
			"void main() {\n"
			"gl_FragColor = lm_fragColor();\n"
			"}\n"
		"";

		const char* vertStr = ""
            "#version 150\n"
			"vec4 lm_position();\n"
			"vec4 lm_texCoord();\n"
			"vec4 lm_frontColor();\n"
			"void main() {\n"
			"gl_Position = lm_position();\n"
			"gl_TexCoord[0] = lm_texCoord();\n"
			"gl_FrontColor = lm_frontColor();\n"
			"}\n"
		"";

		fragLink.load(fragStr, GL_FRAGMENT_SHADER);
		vertLink.load(vertStr, GL_VERTEX_SHADER);
        */
		def.attach(Shader::fragment());
		def.attach(Shader::vertex());
		//def.attach(fragLink);
		//def.attach(vertLink);
		def.link();
		init = true;
	}
	return def;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_program);
}
