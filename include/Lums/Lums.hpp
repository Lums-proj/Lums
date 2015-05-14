/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Lums.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_HPP
#define LUMS_HPP

#define LUMS_STR2(str)      #str
#define LUMS_STR(str)       LUMS_STR2(str)
#define LUMS_VERSION_MAJOR  3
#define LUMS_VERSION_MINOR  0
#define LUMS_VERSION_TEENY  0
#define LUMS_VERSION_PATCH  0

#define LUMS_VERSION_NUMBER LUMS_STR(LUMS_VERSION_MAJOR) "."	\
							LUMS_STR(LUMS_VERSION_MINOR) "." 	\
							LUMS_STR(LUMS_VERSION_TEENY)

#if LUMS_VERSION_PATCH == 0
# define LUMS_VERSION   LUMS_VERSION_NUMBER
#else
# define LUMS_VERSION   LUMS_VERSION_NUMBER "p" LUMS_STR(LUMS_VERSION_PATCH)
#endif

#include <Lums/Angle.hpp>
#include <Lums/Application.hpp>
#include <Lums/Core.hpp>
#include <Lums/Event.hpp>
#include <Lums/Font.hpp>
#include <Lums/GameState.hpp>
#include <Lums/Image.hpp>
#include <Lums/Key.hpp>
#include <Lums/Math.hpp>
#include <Lums/Matrix.hpp>
#include <Lums/OpenGL.hpp>
#include <Lums/OperatingSystem.hpp>
#include <Lums/Projection.hpp>
#include <Lums/Rect.hpp>
#include <Lums/Shader.hpp>
#include <Lums/ShaderProgram.hpp>
#include <Lums/Sound.hpp>
#include <Lums/SoundManager.hpp>
#include <Lums/Sprite.hpp>
#include <Lums/SpriteBatch.hpp>
#include <Lums/Vector.hpp>
#include <Lums/VertexBuffer.hpp>
#include <Lums/Window.hpp>

namespace lm
{
    enum class Module
    {
        Core,
        Graphics,
        Audio,
        All
    };

    namespace internal
    {
        void    _enableSingleModule(Module module);

        inline void
        _enableModule()
        {

        }

        template <typename... Modules>
        inline void
        _enableModule(Module module, Modules... modules)
        {
            _enableSingleModule(module);
            _enableModule(modules...);
        }
    }

    template <typename... Modules>
    inline void
    enableModule(Module module, Modules... modules)
    {
        internal::_enableModule(module, modules...);
    }
}

#endif
