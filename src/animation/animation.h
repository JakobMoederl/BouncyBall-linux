//
// Created by jakob on 20.02.18.
//

#ifndef BOUNCYBALL_LINUX_ANIMATION_H
#define BOUNCYBALL_LINUX_ANIMATION_H

#include <glm/glm.hpp>

#define ANIMATION_LIN2P(percent) (percent < 0.5f ? 2*percent : 2*(1-percent))

//a simple animation class that applies a transformation a model before the MVP

class Animation{
protected:
    //current animation status (time, angle, ect)
    float duration;

public:
    Animation();
    explicit Animation(const float length);
    Animation(const float length, const float animation);
    ~Animation();

    virtual void doStep(const float stepSize);
    void reset();

    //total animation length. set to 0 for never ending animations like rolling balls
    float length;
    //general amplitude for the animation. could be max bounce value, or rotation speed ect.
    float amplitude;

    bool active;
    glm::mat4 mat;

    bool isFinished();

    float getDuration() const;
    void setDuration(const float duration);
};

#endif //BOUNCYBALL_LINUX_ANIMATION_H
