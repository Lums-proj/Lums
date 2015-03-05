/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Music.cpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <Lums/Music.hpp>
#include <thread>

static void
musicHelperMain()
{
	setDevice(NULL);
	while (1)
	{

	}
}

/*
** End of helper
*/

bool helperLaunched = false;

Music::Music()
{
	if (!helperLaunched)
	{
		std::thread t(musicHelperMain);
		t.detach();
		helperLaunched = true;
	}
}

void
Musid::loadFile(const std::string& file, bool resource)
{

}

void
Music::loadOgg(const std::string& file)
{

}

void
Music::play()
{

}

void
Music::pause()
{

}

void
Music::stop()
{

}

Music::~Music()
{

}
