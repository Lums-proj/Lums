/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    BoneAnimation.cpp                              oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <iostream>
#include <LumsInclude/Skeleton/BoneAnimation.hpp>

using namespace lm;

void
BoneAnimation::loadFromFile(std::ifstream& file)
{
    uint32_t boneId;
    uint32_t rotationCount;
    uint32_t translationCount;

    file.read((char*)&boneId, 4);
    file.read((char*)&rotationCount, 4);
    file.read((char*)&translationCount, 4);
    bone = boneId;
    rotations.resize(rotationCount);
    translations.resize(translationCount);
    for (unsigned i = 0; i < rotationCount; ++i)
    {
        auto& r = rotations[i];

        uint32_t frame;
        float angle;

        file.read((char*)&frame, 4);
        file.read((char*)&angle, 4);
        r.frame = frame;
        r.angle = angle;
        r.curve.loadFromFile(file);
    }
    for (unsigned i = 0; i < translationCount; ++i)
    {
        auto& t = translations[i];

        uint32_t frame;
        Vector2f translation;

        file.read((char*)&frame, 4);
        file.read((char*)&translation.x, 4);
        file.read((char*)&translation.y, 4);
        t.frame = frame;
        t.translation = translation;
        t.curve.loadFromFile(file);
    }
}

template <typename T>
static int
lookupKeyFrame(const std::vector<T>& vect, int frame)
{
    for (unsigned i = 0; i < vect.size() - 1; ++i)
    {
        if (frame >= vect[i].frame && frame < vect[i + 1].frame)
            return i;
    }
    return -1;
}

static float
clamp(float angle)
{
    while (angle < 0.f)
        angle += 360.f;
    while (angle >= 360.f)
        angle -= 360.f;
    return angle;
}

float
BoneAnimation::interpolateRotation(int frame) const
{
    int keyFrame = lookupKeyFrame(rotations, frame);
    if (keyFrame == -1)
        return rotations.back().angle;
    const auto& kf0 = rotations[keyFrame];
    const auto& kf1 = rotations[keyFrame + 1];
    float alpha;
    if (kf0.curve.type == KeyFrameCurve::Type::Stepped)
        alpha = 0;
    else
        alpha = float(frame - kf0.frame) / float(kf1.frame - kf0.frame);
    float a0 = clamp(kf0.angle);
    float a1 = clamp(kf1.angle);
    if (fabs(a0 - a1) > 180.f)
    {
        if (a0 < a1)
            a0 += 360.f;
        else
            a1 += 360.f;
    }
    return clamp((1 - alpha) * a0 + alpha * a1);
}

Vector2f
BoneAnimation::interpolateTranslation(int frame) const
{
    int keyFrame = lookupKeyFrame(translations, frame);
    if (keyFrame == -1)
        return translations.back().translation;
    const auto& kf0 = translations[keyFrame];
    const auto& kf1 = translations[keyFrame + 1];
    float alpha;
    if (kf0.curve.type == KeyFrameCurve::Type::Stepped)
        alpha = 0;
    else
        alpha = float(frame - kf0.frame) / float(kf1.frame - kf0.frame);
    Vector2f t0 = kf0.translation;
    Vector2f t1 = kf1.translation;
    return t0 * (1 - alpha) + t1 * alpha;   
}
