/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Attachment.hpp                                 oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_ATTACHMENT_HPP
#define LUMS_SKELETON_ATTACHMENT_HPP

#include <fstream>
#include <LumsInclude/Math/Vector.hpp>
#include <LumsInclude/Math/Matrix.hpp>
#include <LumsInclude/Skeleton/Transformable.hpp>

namespace lm
{
    struct SkeletonPose;
    struct Attachment : public Transformable
    {
        void            loadFromFile(std::ifstream& file);
        Transformable*  parent(SkeletonPose& skeleton) const;

        int             texture;
        int             bone;
    };
}

#endif
