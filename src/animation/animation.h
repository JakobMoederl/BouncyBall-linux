//
// Created by jakob on 20.02.18.
//

#ifndef BOUNCYBALL_LINUX_ANIMATION_H
#define BOUNCYBALL_LINUX_ANIMATION_H

#include <glm/glm.hpp>

//a simple animation class that applies a transformation a model before the MVP

class Animation{
private:
    //general amplitude for the animation. could be max bounce value, or rotation speed ect.
    //animation time
    float duration;

    //for these function a time of 1 means the whole animation length has passed
    glm::mat4 scale;
    glm::mat4 trans;
    glm::mat4 rot;

    glm::vec3 spaceDiff;

public:
    Animation();
    explicit Animation(const float length);
    ~Animation();

    bool doStep(const float timeDiff, const glm::vec3 & spaceDiff);
    void reset();

    const glm::mat4 & getScale() const;
    const glm::mat4 & getRotation() const;
    const glm::mat4 & getTranslation() const;
    glm::vec3 scaleAmpl;
    glm::vec3 rotAxis;
    float rotSpeed;
    glm::vec3 transAmpl;

    //total animation length (time). set to 0 for never ending animations like rolling balls
    float length;
    bool active;

    float getDuration() const;
    void setDuration(const float duration);


    const glm::mat4 (*rotFunction)(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & rotAxis, float rotSpeed);
    const glm::vec3 (*scaleFunction)(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & amplitude);
    const glm::vec3 (*transFunction)(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & amplitude);
    //static function to calculate different for animation paths

    static const glm::vec3 linearTime(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & amplitude);
    static const glm::vec3 linearTime2p(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & amplitude);

    static const glm::mat4 linearRotXSpace(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & rotAxis, float rotSpeed);
};

#endif //BOUNCYBALL_LINUX_ANIMATION_H
