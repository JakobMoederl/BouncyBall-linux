//
// Created by jakob on 20.02.18.
//


#include <cmath>
#include <glm/glm.hpp>

#include "animation.h"

Animation::Animation() {
    Animation::length = 0;
    duration = 0.0f;
    active = false;
    mat = glm::mat4(1.0f);
}

Animation::Animation(const float length) {
    Animation::length = length;
    duration = 0.0f;
    active = false;
    mat = glm::mat4(1.0f);
}

Animation::Animation(const float length, const float amplitude) {
    Animation::length = length;
    Animation::amplitude = amplitude;
    duration = 0.0f;
    mat=glm::mat4(1.0f);
    active = false;

}

Animation::~Animation() {

}

void Animation::reset() {
    active = false;
    Animation::mat = glm::mat4(1.0);
}

float Animation::getDuration() const {
    return duration;
}

void Animation::setDuration(const float duration) {
    if(active) {
        Animation::duration = duration;
        if (isFinished()) {
            active = false;
        }
    }
}

void Animation::doStep(const float stepSize) {
    if(active) {
        setDuration(getDuration() + stepSize);
    }
}

inline bool Animation::isFinished() {
    return length != 0 && duration > length;
}


