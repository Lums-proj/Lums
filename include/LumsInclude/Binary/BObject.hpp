/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BObject.hpp                                    oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BOBJECT_HPP
#define LUMS_BOBJECT_HPP

namespace lm
{
    struct BPair;

    struct BObject
    {
    public:

    private:
        int         size;
        BObject*    objects;
    };
}

#endif
