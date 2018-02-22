//
// Created by jakob on 21.02.18.
//

#ifndef BOUNCYBALL_LINUX_ANIMATION_BOUNCE_H
#define BOUNCYBALL_LINUX_ANIMATION_BOUNCE_H

#include "animation.h"

class AnimationBounce : public Animation{
private:
    //0=bounce in x direction, 1=y, 2=z
    glm::vec3 bounceAmplitude;
public:
    AnimationBounce();
    AnimationBounce(const float lenght);
    AnimationBounce(const float length, const float amplitude);
    void doStep(const float timeDiff);
};


#endif //BOUNCYBALL_LINUX_ANIMATION_BOUNCE_H
