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

#include <string>
#include <LumsInclude/Binary/BValue.hpp>

namespace lm
{
    class BFile
    {
    public:
        BFile();
        void    open(const std::string& path, bool resource = true);
        ~BFile();

    private:
        int         _size;
        BValue*     _values;
    };
}

#endif
