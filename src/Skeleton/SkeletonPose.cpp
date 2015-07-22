/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonPose.cpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
#include <cstdint>
#include <fstream>
#include <LumsInclude/Skeleton/SkeletonPose.hpp>
#include <LumsInclude/OperatingSystem.hpp>

using namespace lm;

SkeletonPose::SkeletonPose()
{

}

void
SkeletonPose::loadFromFile(std::ifstream& file)
{
    uint32_t boneCount;
    file.read((char*)&boneCount, 4);
    for (unsigned i = 0; i < boneCount; ++i)
    {
        int32_t nameLen;
        char* name;
        int32_t parent;
        float length;
        lm::Vector2f position;
        lm::Vector2f scale;
        float rotation;
        bool ir;

        file.read((char*)&nameLen, 4);
        name = new char[nameLen + 1];
        name[nameLen] = 0;
        delete [] name;
        file.read(name, nameLen);
        file.read((char*)&parent, 4);
        file.read((char*)&length, 4);
        file.read((char*)&position.x, sizeof(float));
        file.read((char*)&position.y, sizeof(float));
        file.read((char*)&scale.x, sizeof(float));
        file.read((char*)&scale.y, sizeof(float));
        file.read((char*)&rotation, sizeof(float));
        file.read((char*)&ir, 1);

        Bone b(parent);
        b.setInheritRotation(ir);
        b.setRotation(rotation);
        b.setPosition(position);
        b.setLength(length);
        _bones.push_back(b);
        if (parent != -1)
            _bones[parent].addChild(i);
    }

    uint32_t skinCount;
    file.read((char*)&skinCount, 4);
    for (unsigned i = 0; i < skinCount; ++i)
    {
        int bone;
        int texture;
        lm::Vector2f position;
        float rotation;

        file.read((char*)&texture, 4);
        file.read((char*)&bone, 4);
        file.read((char*)&position.x, sizeof(float));
        file.read((char*)&position.y, sizeof(float));
        file.read((char*)&rotation, sizeof(float));

        Skin s(bone, texture);
        s.setRotation(rotation);
        s.setPosition(position);
        _skins.push_back(s);
    }
    update();
}

void
SkeletonPose::update()
{
    for (auto& b : _bones)
        b.updateWorldTransform(*this);
    for (auto& s : _skins)
        s.updateWorldTransform(*this);
}
