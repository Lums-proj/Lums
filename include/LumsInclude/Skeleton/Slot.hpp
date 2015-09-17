/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Slot.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_SLOT_HPP
#define LUMS_SKELETON_SLOT_HPP

#include <fstream>

namespace lm
{
    struct Slot
    {
        void    loadFromFile(std::ifstream& file);
        
        int     bone;
        int     attachment;
    };
}

#endif
