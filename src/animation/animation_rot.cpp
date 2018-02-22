//
// Created by jakob on 21.02.18.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "animation_rot.h"

AnimationRot::AnimationRot() {
    rotVec = glm::vec3(0.0f, 0.0f, -1.0f);
}

AnimationRot::AnimationRot(const float length) : Animation(length) {
    rotVec = glm::vec3(0.0f, 0.0f, -1.0f);
}

AnimationRot::AnimationRot(const float length, const float amplitude) : Animation(length, amplitude) {
    rotVec = glm::vec3(0.0f, 0.0f, -1.0f);
}

AnimationRot::~AnimationRot() {

}

void AnimationRot::doStep(const float stepSize) {
        //update the animation duration - set the amplitude to 1/radius to get a rolling effect
        Animation::doStep(stepSize);
        //update the animation matrix
        if(active) {
            mat = glm::rotate(glm::mat4(1.0f),  amplitude*getDuration(), rotVec);
        }
}
