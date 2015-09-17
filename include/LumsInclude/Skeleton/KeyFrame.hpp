/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    KeyFrame.hpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_KEY_FRAME_HPP
#define LUMS_KEY_FRAME_HPP

#include <fstream>
#include <vector>
#include <LumsInclude/Math/Vector.hpp>

namespace lm
{
    struct KeyFrame
    {
        void    loadFromFile(std::ifstream& file);

        int     frame;

        template <typename T>
        static int
        lookup(const std::vector<T>& vect, int frame)
        {
            for (unsigned i = 0; i < vect.size() - 1; ++i)
            {
                if (frame >= vect[i].frame && frame < vect[i + 1].frame)
                    return i;
            }
            return -1;
        }
    };
}

#endif
