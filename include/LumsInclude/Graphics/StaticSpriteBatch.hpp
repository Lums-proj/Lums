/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    StaticSpriteBatch.hpp                          oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_STATIC_SPRITE_BATCH_HPP
#define LUMS_STATIC_SPRITE_BATCH_HPP

#include <LumsInclude/Graphics/VertexBuffer.hpp>
#include <LumsInclude/Graphics/Texture.hpp>
#include <LumsInclude/Graphics/Sprite.hpp>
#include <LumsInclude/Graphics/Font.hpp>
#include <LumsInclude/ExportDll.hpp>

namespace lm
{
    class StaticSpriteBatch
    {
    public:
        StaticSpriteBatch();
        LUMS_EXPORTED void              draw(const Texture& texture,
                                             int atlas = 0,
                                             Vector2f pos = {0.f, 0.f},
                                             Vector2f scale = {1.f, 1.f},
                                             Vector4f color = {1.f, 1.f, 1.f, 1.f},
                                             Vector2b flip = {false, false});
        LUMS_EXPORTED void              draw(const Sprite& sprite);
        LUMS_EXPORTED void              draw(const Font& font,
                                             const char* text,
                                             Vector2f pos = {0.f, 0.f},
                                             Vector4f color = {1.f, 1.f, 1.f, 1.f});
        LUMS_EXPORTED virtual void      setTexture(const Texture* texture);
        LUMS_EXPORTED void              send();
        LUMS_EXPORTED void              flush();
        LUMS_EXPORTED void              render();
        ~StaticSpriteBatch();

    protected:
        VertexBufferP2T2C4          _vbo;
        const Texture*              _texture;
    };
};

#endif
