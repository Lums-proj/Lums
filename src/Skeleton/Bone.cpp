/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Bone.cpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/Skeleton/Bone.hpp>
#include <LumsInclude/Skeleton/SkeletonPose.hpp>

using namespace lm;

void
Bone::loadFromFile(std::ifstream& file)
{
    uint32_t nameLen;
    char* name;
    file.read((char*)&nameLen, 4);
    name = new char[nameLen + 1];
    name[nameLen] = 0;
    file.read(name, nameLen);
    this->name = lm::sym(name);
    delete [] name;

    Transformable::loadFromFile(file);
    file.read((char*)&length, 4);
    file.read((char*)&parentBone, 4);

    char ir;
    file.read((char*)&ir, 1);
    inheritRotation = ir;
}

Transformable*
Bone::parent(SkeletonPose& skeleton) const
{
    if (parentBone != -1)
        return &skeleton.bones[parentBone];
    return nullptr;
}
