/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BFile.hpp                                      oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BFILE_HPP
#define LUMS_BFILE_HPP

#include <LumsInclude/Binary/BObject.hpp>

namespace lm
{
    class BFile
    {
    public:


    private:
        int         _size;
        BObject*    _objects;
    };
}

#endif
