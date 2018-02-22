//
// Created by jakob on 21.02.18.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include "animation_bounce.h"

AnimationBounce::AnimationBounce() {

}

AnimationBounce::AnimationBounce(const float length, const float amplitude) : Animation(length, amplitude) {

}

void AnimationBounce::doStep(const float stepSize) {
    Animation::doStep(stepSize);
    if(active){
        mat = glm::scale(glm::mat4(1.0f), glm::vec3(1) + bounceAmplitude*amplitude*ANIMATION_LIN2P(getDuration()));
    }
}