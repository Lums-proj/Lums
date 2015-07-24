/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Graphics.cpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Graphics/Graphics.hpp>
#include <LumsInclude/Provider.hpp>

namespace lm
{
    static float gScale = 1.f;

    void
    setGlobalScale(float scale)
    {
        gScale = scale;
        lm::TextureProvider::instance().reloadAll();
        lm::FontProvider::instance().reloadAll();
    }
    
    float
    globalScale()
    {
        return gScale;
    }
}
