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

#include <vector>
#include <LumsInclude/Math/Vector.hpp>

namespace lm
{
    class Bone
    {
    public:
        using Array = std::vector<int>;

        Bone(int parent);
        
        bool            root() const { return _parent == -1; }
        int             parent() const { return _parent; }
        const Array&    children() const { return _children; }

        void            addChild(int child) { _children.push_back(child); }
        void            setPosition(const lm::Vector2f& position) { _position = position; }
        void            setScale(const lm::Vector2f& scale) { _scale = scale; }
        void            setRotation(float rotation) { _rotation = rotation; }

        lm::Vector2f    position() const { return _position; }
        lm::Vector2f    scale() const { return _scale; }
        float           rotation() const { return _rotation; }

        ~Bone();

    private:
        int                     _parent;
        Array                   _children;
        lm::Vector2f            _position;
        lm::Vector2f            _scale;
        float                   _rotation;
    };
}

#endif
