//
// Created by jakob on 21.02.18.
//

#ifndef BOUNCYBALL_LINUX_ANIMATION_BOUNCE_H
#define BOUNCYBALL_LINUX_ANIMATION_BOUNCE_H

#include "animation.h"

class AnimationBounce : public Animation{
private:
    //0=bounce in x direction, 1=y, 2=z
    uint direction;
public:
    AnimationBounce();
    AnimationBounce(const unsigned int direction);
    AnimationBounce(const unsigned int direction, const float length);
    AnimationBounce(const unsigned int direction, const float length, const float amplitude);
    const unsigned int getDirection() const;
    void setDirection(const unsigned int direction);
    void doStep(const float timeDiff);
};


#endif //BOUNCYBALL_LINUX_ANIMATION_BOUNCE_H
