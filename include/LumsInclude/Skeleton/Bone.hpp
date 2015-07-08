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
#include <LumsInclude/Math/Matrix.hpp>
#include <LumsInclude/Graphics/OpenGL.hpp>


namespace lm
{
    class Bone
    {
    public:
        using Array = std::vector<int>;

        Bone(int parent);
        
        bool                root() const { return _parent == -1; }
        int                 parent() const { return _parent; }
        const Array&        children() const { return _children; }

        void                addChild(int child) { _children.push_back(child); }
        void                translate(Vector3f v) { ::lm::translate(_transform, v); }
        void                rotate(float r) { ::lm::rotate(_transform, r, { 0.f, 0.f, -1.f }); }

        const Matrix4f&     transform() const { return _transform; }

        ~Bone();

    private:
        int                 _parent;
        Array               _children;
        Matrix4f            _transform;
    };
}

#endif
