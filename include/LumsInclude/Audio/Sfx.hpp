/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Sfx.hpp                                        oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SFX_HPP
#define LUMS_SFX_HPP

#include <vector>
#include <LumsInclude/Audio/Sound.hpp>

namespace lm
{
    class Sfx : public Sound
    {
    public:
        Sfx();
        void    play(Vector3f pos = {0.f, 0.f, 0.f});
        void    pause();
        void    stop();
        ~Sfx();
    private:

        std::vector<ALuint> _sources;
    };
}

#endif