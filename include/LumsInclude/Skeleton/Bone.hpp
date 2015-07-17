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
    class SkeletonPose;

    class Bone
    {
    public:
        friend class Skin;

        using Array = std::vector<int>;

        Bone(int parent);

        bool                root() const { return _parent == -1; }
        int                 parent() const { return _parent; }
        const Array&        children() const { return _children; }
        void                addChild(int child) { _children.push_back(child); }

        void                setInheritRotation(bool ir) { _inheritRotation = ir; }
        void                setPosition(const Vector2f& position) { _position = position; }
        void                setRotation(float rotation) { _rotation = rotation; }

        bool                inheritRotation() const { return _inheritRotation; }
        const Vector2f&     worldPosition() const { return _worldPosition; }
        float               worldRotation() const { return _worldRotation; }

        void                transform(Matrix4f& matrix) const;

        void                updateWorldTransform(const SkeletonPose& skeleton);

        ~Bone();

    private:
        int                 _parent;
        Array               _children;
        Vector2f            _position;
        float               _rotation;
        Vector2f            _worldPosition;
        float               _worldRotation;
        Matrix2f            _worldRotMatrix;
        bool                _inheritRotation;
    };
}

#endif
