/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Attachment.cpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Attachment.hpp>
#include <LumsInclude/Skeleton/SkeletonPose.hpp>

using namespace lm;

void
Attachment::loadFromFile(std::ifstream& file)
{
    Transformable::loadFromFile(file);
    file.read((char*)&texture, 4);
}

Transformable*
Attachment::parent(SkeletonPose& skeleton) const
{
    return &skeleton.bones[bone];
}
