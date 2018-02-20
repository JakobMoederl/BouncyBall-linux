//
// Created by jakob on 20.02.18.
//

#ifndef BOUNCYBALL_LINUX_ANIMATION_H
#define BOUNCYBALL_LINUX_ANIMATION_H

#include <glm/glm.hpp>

//a simple animation class that applies a transformation a model before the MVP

class Animation{
private:
    bool active;
    //total animation length. set to 0 for never ending animations like rolling balls
    float length;
    //general amplitude for the animation. could be max bounce value, or rotation speed ect.
    float amplitude;
    //current animation status (time, angle, ect)
    float duration;
    glm::mat4 mat;

public:
    Animation();
    explicit Animation(const float length);
    Animation(const float length, const float animation);
    ~Animation();

    void doStep(const float stepSize);
    void start();
    void reset();

    const glm::mat4 & getMatrix() const;
    void setMatrix(const glm::mat4 & mat);
    float getLength() const;
    void setLength(const float length);
    float getAmplitude() const;
    void setAmplitude(const float amplitude);
    float getDuration() const;
    void setDuration(const float duration);
    bool isActive() const;
    void setActive(const bool isActive);

};

#endif //BOUNCYBALL_LINUX_ANIMATION_H
