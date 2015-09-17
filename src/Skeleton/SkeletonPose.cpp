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

void
SkeletonPose::loadFromFile(std::ifstream& file)
{
    uint32_t boneCount;
    file.read((char*)&boneCount, 4);
    bones.resize(boneCount);
    for (auto& b : bones)
        b.loadFromFile(file);

    uint32_t slotCount;
    file.read((char*)&slotCount, 4);
    slots.resize(slotCount);
    for (auto& s : slots)
        s.loadFromFile(file);

    uint32_t attachmentCount;
    file.read((char*)&attachmentCount, 4);
    attachments.resize(attachmentCount);
    for (auto& attachment : attachments)
        attachment.loadFromFile(file);

    uint32_t ikCount;
    file.read((char*)&ikCount, 4);
    iks.resize(ikCount);
    for (auto& ik : iks)
        ik.loadFromFile(file);

    update();
}

void
SkeletonPose::update()
{
    for (auto& b : bones)
        b.update(*this);
    for (auto& a : attachments)
    {
        if (a.bone != -1)
            a.update(*this);
    }
}
