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
    /**
     * @brief A class used to represent sound effect
     */
    class Sfx : public Sound
    {
    public:
        /**
         * Create an empty sound effect
         */
        Sfx();

        /**
         * Deleted ctor
         */
        Sfx(const Sfx&) = delete;

        /**
         * Move-construct ctor
         * @param rhs Source sound effect
         */
        Sfx(Sfx&& rhs);

        /**
         * Deleted assignment operator
         */
        Sfx&  operator=(const Sfx&) = delete;

        /**
         * Move-assign a sound effect
         * @param rhs Source sound effect
         */
        Sfx&  operator=(Sfx&& rhs);

        /**
         * Play the loaded sound effect
         * @param pos Source position
         */
        void    play(Vector3f pos = {0.f, 0.f, 0.f});

        /**
         * Pause the loaded sound effect
         */
        void    pause();

        /**
         * Stop the loaded sound effect
         */
        void    stop();

        /**
         * Set the volume of the loaded sound effect
         * @param volume The volume, 0 being silent and 1 the loudest
         */
        void    setVolume(float volume);

        /**
         * Sound dtor
         */
        ~Sfx();

    private:
        std::vector<ALuint> _sources;
    };

    using SfxProvider = StreamProvider<Sfx>;
}

#endif