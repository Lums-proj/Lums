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

#include <LumsInclude/Application.hpp>
#include <LumsInclude/Common.hpp>
#include <LumsInclude/Core/Core.hpp>
#include <LumsInclude/Core/GameState.hpp>
#include <LumsInclude/GameObject/Component.hpp>
#include <LumsInclude/GameObject/GameObject.hpp>
#include <LumsInclude/ExportDll.hpp>
#include <LumsInclude/Graphics/Event.hpp>
#include <LumsInclude/Graphics/Font.hpp>
#include <LumsInclude/Graphics/Image.hpp>
#include <LumsInclude/Graphics/Key.hpp>
#include <LumsInclude/Graphics/OpenGL.hpp>
#include <LumsInclude/Audio/Sfx.hpp>
#include <LumsInclude/Graphics/Shader.hpp>
#include <LumsInclude/Graphics/ShaderPipeline.hpp>
#include <LumsInclude/Graphics/ShaderProgram.hpp>
#include <LumsInclude/Audio/Sound.hpp>
#include <LumsInclude/Graphics/Sprite.hpp>
#include <LumsInclude/Graphics/SpriteBatch.hpp>
#include <LumsInclude/Graphics/StaticSpriteBatch.hpp>
#include <LumsInclude/Graphics/VertexBuffer.hpp>
#include <LumsInclude/Graphics/Window.hpp>
#include <LumsInclude/Math/Angle.hpp>
#include <LumsInclude/Math/Math.hpp>
#include <LumsInclude/Math/Matrix.hpp>
#include <LumsInclude/Audio/Music.hpp>
#include <LumsInclude/Math/Projection.hpp>
#include <LumsInclude/Math/Rect.hpp>
#include <LumsInclude/Math/Vector.hpp>
#include <LumsInclude/OperatingSystem.hpp>
#include <LumsInclude/Provider.hpp>
#include <LumsInclude/Singleton.hpp>

/**
 * @brief The Lums namespace
 */
namespace lm
{
    /**
     * This enum defines a Module.
     * A module can be loaded using enableModule().
     */
    enum class Module
    {
        Core,
        Graphics,
        Audio,
        All
    };

    /**
     * @cond
     */
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
    /**
     * @endcond
     */

    /**
     * Enable one or more modules.
     * You can use the special enum member Module::All to
     * enable every module.
     */
    template <typename... Modules>
    inline void
    enableModule(Module module, Modules... modules)
    {
        internal::_enableModule(module, modules...);
    }
}

#endif
