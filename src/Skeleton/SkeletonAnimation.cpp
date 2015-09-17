/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonAnimation.cpp                          oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <LumsInclude/Skeleton/SkeletonAnimation.hpp>

using namespace lm;

void
SkeletonAnimation::loadFromFile(std::ifstream& file)
{
    uint32_t boneCount;
    file.read((char*)&boneCount, 4);
    bones.resize(boneCount);
    for (auto& b : bones)
        b.loadFromFile(file);

    uint32_t ikCount;
    file.read((char*)&ikCount, 4);
    iks.resize(ikCount);
    for (auto& ik : iks)
        ik.loadFromFile(file);

    uint32_t eventCount;
    file.read((char*)&eventCount, 4);
    events.resize(eventCount);
    for (auto& event : events)
        event.loadFromFile(file);

    uint32_t slotCount;
    file.read((char*)&slotCount, 4);
    slots.resize(slotCount);
    for (auto& slot : slots)
        slot.loadFromFile(file);

    computeLength();
}

void
SkeletonAnimation::computeLength()
{
    int max = 0;

    for (auto& b : bones)
    {
        if (!b.translations.empty())
        {
            auto& t = b.translations.back();
            if (t.frame > max)
                max = t.frame;
        }
        if (!b.rotations.empty())
        {
            auto& r = b.rotations.back();
            if (r.frame > max)
                max = r.frame;
        }
    }
    length = max;
}

size_t
SkeletonAnimation::getEvent(int frame) const
{
    static const size_t nullEvent = lm::sym("");

    for (auto& e : events)
    {
        if (e.frame == frame)
            return e.event;
    }
    return nullEvent;
}
