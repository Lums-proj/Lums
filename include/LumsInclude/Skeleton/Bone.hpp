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
        void                setLength(float length) { _length = length; }
        void                setScale(const Vector2f& scale) { _scale = scale; }

        bool                inheritRotation() const { return _inheritRotation; }
        const Vector2f&     position() const { return _position; }
        const Vector2f&     worldPosition() const { return _worldPosition; }
        float               rotation() const { return _rotation; }
        float               worldRotation() const { return _worldRotation; }
        float               length() const { return _length; }

        void                transform(Matrix4f& matrix) const;

        void                worldToLocal(lm::Vector2f& world) const;
        void                updateWorldTransform(const SkeletonPose& skeleton);

        ~Bone();

    private:
        int                 _parent;
        Array               _children;
        Vector2f            _position;
        float               _rotation;
        Vector2f            _scale;
        float               _length;
        Vector2f            _worldPosition;
        float               _worldRotation;
        Matrix2f            _worldRotMatrix;
        Vector2f            _worldScale;
        bool                _inheritRotation;
    };
}

#endif
