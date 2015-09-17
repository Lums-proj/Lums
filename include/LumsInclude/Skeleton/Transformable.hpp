/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Transformable.hpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_SKELETON_TRANSFORMABLE_HPP
#define LUMS_SKELETON_TRANSFORMABLE_HPP

#include <fstream>
#include <LumsInclude/Math/Matrix.hpp>
#include <LumsInclude/Graphics/OpenGL.hpp>

namespace lm
{
    struct SkeletonPose;
    struct Transformable
    {
        void                    loadFromFile(std::ifstream& file);
        void                    update(SkeletonPose& skeleton);
        virtual Transformable*  parent(SkeletonPose& skeleton) const = 0;
        virtual bool            doesInheritRotation() const = 0;
        bool                    isDirty(SkeletonPose& skeleton) const { return dirty ? true : (parent(skeleton) ? parent(skeleton)->isDirty(skeleton) : false); }
        void                    transform(Matrix4f& mat) const;
        void                    worldToLocal(lm::Vector2f& local) const;

        lm::Vector2f    position;
        lm::Vector2f    scale;
        float           rotation;

        lm::Vector2f    worldPosition;
        lm::Vector2f    worldScale;
        float           worldRotation;

        lm::Matrix2f    matrix;
        bool            dirty = true;
    };
}

#endif
