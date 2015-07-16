/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    SkeletonPose.hpp                               oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_POSE_HPP
#define LUMS_SKELETON_POSE_HPP

#include <fstream>
#include <vector>
#include <LumsInclude/Provider.hpp>
#include <LumsInclude/Skeleton/Bone.hpp>
#include <LumsInclude/Skeleton/Skin.hpp>

namespace lm
{
    class SkeletonPose
    {
    public:
    	SkeletonPose();
        
        void        load(std::ifstream& file);

        void        update();
        
        const std::vector<Bone>&    bones() const { return _bones; }
        const std::vector<Skin>&    skins() const { return _skins; }

    private:
        std::vector<Bone>   _bones;
        std::vector<Skin>   _skins;
    };
}

#endif
