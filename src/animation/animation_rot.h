//
// Created by jakob on 21.02.18.
//

#ifndef BOUNCYBALL_LINUX_ANIMATION_ROT_H
#define BOUNCYBALL_LINUX_ANIMATION_ROT_H

#include "animation.h"

//derivations of Animation
class AnimationRot: public Animation {
public:
    AnimationRot();
    AnimationRot(const float length);
    AnimationRot(const float length, const float amplitude);
    ~AnimationRot();
    void doStep(const float timeDiff);
};



#endif //BOUNCYBALL_LINUX_ANIMATION_ROT_H
