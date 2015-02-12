/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Script.cpp                                     oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/dump.h>
#include <mruby/proc.h>
#include <Lums/Script.hpp>
#include <Lums/OperatingSystem.hpp>

using namespace lm;

static mrb_state* mrb = nullptr;

Script::Script()
: _proc(nullptr)
{
	if (!mrb)
		mrb = mrb_open();
}

Script::Script(Script&& rhs)
: _proc(rhs._proc)
{
	rhs._proc = nullptr;
}

void
Script::loadFile(const std::string& filename, bool resource)
{
	FILE* f;
	std::string file;

	if (resource)
		file = resourcePath() + '/' + filename;
	else
		file = filename;
	f = fopen(file.c_str(), "rb");
	if (!f)
	{
		std::cerr << "Error: cannot open script '" << file << "'" << std::endl;
		return;
	}
	mrb_irep* irep = mrb_read_irep_file(mrb, f);
	fclose(f);
	_proc = mrb_proc_new(mrb, irep);
}

void
Script::run()
{
	mrb_run(mrb, static_cast<RProc*>(_proc), mrb_top_self(mrb));
}

Script
Script::load(const std::string& filename, bool resource)
{
	Script script;

	script.loadFile(filename, resource);
	return script;
}

Script::~Script()
{

}
