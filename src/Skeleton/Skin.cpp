/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Skin.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Skin.hpp>

using namespace lm;

Skin::Skin(int bone, int texture)
: _bone(bone)
, _texture(texture)
, _transform(Matrix4f::identity())
{

}

Skin::~Skin()
{

}
