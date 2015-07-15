/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Skin.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKIN_HPP
#define LUMS_SKIN_HPP

#include <LumsInclude/Math/Matrix.hpp>
#include <LumsInclude/Graphics/OpenGL.hpp>

namespace lm
{
    class Skeleton;

    class Skin
    {
    public:
        Skin(int bone, int texture);

        void                setTexture(int texture) { _texture = texture; }
        void                setPosition(const Vector2f& position) { _position = position; }
        void                setRotation(float rotation) { _rotation = rotation; }
        
        int                 bone() const { return _bone; }
        int                 texture() const { return _texture; }
        const Vector2f&     worldPosition() const { return _worldPosition; }
        float               worldRotation() const { return _worldRotation; }

        void                updateWorldTransform(const Skeleton& skeleton);

        ~Skin();

    private:
        int             _bone;
        int             _texture;
        Vector2f        _position;
        float           _rotation;
        Vector2f        _worldPosition;
        float           _worldRotation;
    };
}

#endif
