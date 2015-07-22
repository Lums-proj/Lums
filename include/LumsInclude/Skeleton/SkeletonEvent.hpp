/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonEvent.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_EVENT_HPP
#define LUMS_SKELETON_EVENT_HPP

#include <fstream>

namespace lm
{
    struct SkeletonEvent
    {
        void    loadFromFile(std::ifstream& file);

        unsigned    frame;
        size_t      name;
    };
}

#endif
