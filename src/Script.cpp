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
#include <Lums/Script.hpp>
#include <Lums/OperatingSystem.hpp>

using namespace lm;

mrb_state* Script::_mrb = nullptr;

Script::Script()
: _proc(nullptr)
{
	if (!_mrb)
		_mrb = mrb_open();
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
	mrb_irep* irep = mrb_read_irep_file(_mrb, f);
	fclose(f);
	_proc = mrb_proc_new(_mrb, irep);
}

void
Script::run()
{
	mrb_run(_mrb, _proc, mrb_top_self(_mrb));
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
