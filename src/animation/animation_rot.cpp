//
// Created by jakob on 21.02.18.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "animation_rot.h"

AnimationRot::AnimationRot() {

}

AnimationRot::AnimationRot(const float length) : Animation(length) {

}

AnimationRot::AnimationRot(const float length, const float amplitude) : Animation(length, amplitude) {

}

AnimationRot::~AnimationRot() {

}

void AnimationRot::doStep(const float stepSize) {
    //update the animation duration - set the amplitude to 1/radius to get a rolling effect
    Animation::doStep(stepSize);
    //update the animation matrix
    setMatrix(glm::rotate(getMatrix(), getAmplitude()*stepSize, glm::vec3(0.0f, 0.0f, 1.0f)));
}
