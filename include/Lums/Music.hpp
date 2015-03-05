/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Music.hpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_MUSIC_HPP
#define LUMS_MUSIC_HPP

#include <OpenAL/al.h>
#include <vorbis/vorbisfile.h>

namespace lm
{
	class Music
	{
	public:
		Music();
		void	loadFile(const std::string& file, bool resource = true);
		void	loadOgg(const std::string& file);
		void	play();
		void	pause();
		void	stop();
		~Music();
	private:

		OggVorbis_File	_file;
	};
}

#endif