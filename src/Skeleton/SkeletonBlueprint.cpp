/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonBlueprint.cpp                          oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <LumsInclude/OperatingSystem.hpp>
#include <LumsInclude/Skeleton/SkeletonBlueprint.hpp>

using namespace lm;

SkeletonBlueprint::SkeletonBlueprint()
{

}

void
SkeletonBlueprint::loadBinary(const BObject& object)
{
    std::string path = object["path"].asString();
    load(path);
}

void
SkeletonBlueprint::load(const std::string& path, bool resource)
{
    std::string fpath = resource ? resourcePath() + path : path;
    std::ifstream file(fpath);
    _data.loadFromFile(file);
}

SkeletonBlueprint::~SkeletonBlueprint()
{

}
