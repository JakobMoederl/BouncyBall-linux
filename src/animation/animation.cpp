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

}

Animation::~Animation() {

}

void Animation::reset() {
    setActive(false);
    Animation::mat = glm::mat4(1.0);
}

bool Animation::isActive() const {
    return active;
}

void Animation::setActive(const bool isActive) {
    Animation::active = isActive;
}

float Animation::getDuration() const {
    return duration;
}

void Animation::setDuration(const float duration) {
    if(active) {
        Animation::duration = duration;
        if (length != 0 && duration > length) {
            setActive(false);
        }
    }
}

void Animation::doStep(const float stepSize) {
    setDuration(getDuration() + stepSize);
}

void Animation::start() {
    setActive(true);
    duration = 0;
    mat = glm::mat4(1.0f);
}

float Animation::getLength() const {
    return length;
}

void Animation::setLength(const float length) {
    Animation::length = length;
}

const glm::mat4 & Animation::getMatrix() const{
    return mat;
}

void Animation::setMatrix(const glm::mat4 & mat) {
    if(active) {
        Animation::mat = mat;
    }
}

float Animation::getAmplitude() const {
    return amplitude;
}

void Animation::setAmplitude(const float amplitude) {
    Animation::amplitude = amplitude;
}


