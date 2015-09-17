/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Ik.hpp                                         oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_IK_HPP
#define LUMS_SKELETON_IK_HPP

#include <fstream>

namespace lm
{
    struct Ik
    {
        void    loadFromFile(std::ifstream& file);

        int     target;
        int     bones[2];
        bool    bendPositive;
    };
}

#endif
