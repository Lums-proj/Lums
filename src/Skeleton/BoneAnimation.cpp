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
#include <LumsInclude/Skeleton/BoneAnimation.hpp>
#include <LumsInclude/Math/Math.hpp>

using namespace lm;

void
BoneAnimation::loadFromFile(std::ifstream& file)
{
    file.read((char*)&bone, 4);

    uint32_t translationCount;
    file.read((char*)&translationCount, 4);
    translations.resize(translationCount);
    for (auto& t : translations)
        t.loadFromFile(file);

    uint32_t rotationCount;
    file.read((char*)&rotationCount, 4);
    rotations.resize(rotationCount);
    for (auto& r : rotations)
        r.loadFromFile(file);
}

float
BoneAnimation::getRotation(int frame) const
{
    if (rotations.empty())
        return 0.f;
    int keyFrame = KeyFrame::lookup(rotations, frame);
    if (keyFrame == -1)
        return rotations.back().rotation;
    const auto& kf0 = rotations[keyFrame];
    const auto& kf1 = rotations[keyFrame + 1];
    float alpha;
    if (kf0.curve.type == KeyFrameCurve::Type::Stepped)
        alpha = 0;
    else
        alpha = float(frame - kf0.frame) / float(kf1.frame - kf0.frame);
    if (kf0.curve.type == KeyFrameCurve::Type::Bezier)
        alpha = bezier4(kf0.curve.c0, kf0.curve.c1, alpha);
    return interpolateAngle(kf0.rotation, kf1.rotation, alpha);
}

Vector2f
BoneAnimation::getTranslation(int frame) const
{
    if (translations.empty())
        return {0.f, 0.f};
    int keyFrame = KeyFrame::lookup(translations, frame);
    if (keyFrame == -1)
        return translations.back().translation;
    const auto& kf0 = translations[keyFrame];
    const auto& kf1 = translations[keyFrame + 1];
    float alpha;
    if (kf0.curve.type == KeyFrameCurve::Type::Stepped)
        alpha = 0;
    else
        alpha = float(frame - kf0.frame) / float(kf1.frame - kf0.frame);
    if (kf0.curve.type == KeyFrameCurve::Type::Bezier)
        alpha = bezier4(kf0.curve.c0, kf0.curve.c1, alpha);
    Vector2f t0 = kf0.translation;
    Vector2f t1 = kf1.translation;
    return t0 * (1 - alpha) + t1 * alpha;   
}
