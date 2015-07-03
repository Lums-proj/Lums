/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Skeleton.hpp                                   oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_HPP
#define LUMS_SKELETON_HPP

#include <string>
#include <vector>
#include <LumsInclude/Provider.hpp>
#include <LumsInclude/Skeleton/Bone.hpp>
#include <LumsInclude/Skeleton/Skin.hpp>

namespace lm
{
    class Skeleton
    {
    public:
    	Skeleton();
        void    load(const std::string& path, bool resource = true);
        void    loadBinary(const BObject& object);

    private:
        std::vector<Bone>   _bones;
        std::vector<Skin>   _skins;
        Texture*			_texture;
    };

    using SkeletonProvider = Provider<Skeleton>;
}

#endif
