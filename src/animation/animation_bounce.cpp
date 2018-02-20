//
// Created by jakob on 21.02.18.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "animation_bounce.h"

AnimationBounce::AnimationBounce() {

}

AnimationBounce::AnimationBounce(const unsigned int direction) : Animation() {
    AnimationBounce::direction = direction;
}

AnimationBounce::AnimationBounce(const unsigned int direction, const float length) : Animation(length) {
    AnimationBounce::direction = direction;
}

AnimationBounce::AnimationBounce(const unsigned int direction, const float length, const float amplitude) : Animation(length, amplitude) {
    AnimationBounce::direction = direction;
}

void AnimationBounce::doStep(const float stepSize) {
    Animation::doStep(stepSize);
    static glm::vec3 scaleVec = glm::vec3(1.0f);
    scaleVec[direction] = getAmplitude()*glm::fastCos(M_2_PI*getDuration());
    setMatrix(glm::scale(glm::mat4(1.0f), scaleVec));
}

const unsigned int AnimationBounce::getDirection() const {
    return direction;
}

void AnimationBounce::setDirection(const unsigned int direction) {
    AnimationBounce::direction = direction;
}