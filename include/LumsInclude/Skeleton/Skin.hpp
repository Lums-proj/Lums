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
    class Skin
    {
    public:
        Skin(int bone, int texture);

        void                setTexture(int texture) { _texture = texture; }
        void                translate(Vector3f v) { ::lm::translate(_transform, v); }
        void                rotate(float r) { ::lm::rotate(_transform, r, { 0.f, 0.f, -1.f }); }
        
        int                 bone() const { return _bone; }
        int                 texture() const { return _texture; }
        const Matrix4f&     transform() const { return _transform; }

        ~Skin();

    private:
        int         _bone;
        int         _texture;
        Matrix4f    _transform;
    };
}

#endif
