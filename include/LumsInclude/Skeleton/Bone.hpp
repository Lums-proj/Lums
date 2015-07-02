/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Bone.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_BONE_HPP
#define LUMS_BONE_HPP

#include <list>

namespace lm
{
    class Bone
    {
    public:
        using Array = std::vector<int>;

        Bone();
        Bone(size_t parent);
        bool            root() const { return _root; }
        size_t          parent() const { return _parent; }
        const Array&    children() const { return _children; }

    private:
        bool                    _root;
        int                     _parent;
        Array                   _children;
    };
}

#endif
