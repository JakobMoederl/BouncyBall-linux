//
// Created by jakob on 20.02.18.
//

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "animation.h"

Animation::Animation() {
    Animation::length = 0;
    duration = 0.0f;
    active = false;
    scale = glm::mat4(1.0f);
    rot = glm::mat4(1.0f);
    trans = glm::mat4(1.0f);
    scaleFunction = NULL;
    rotFunction = NULL;
    transFunction = NULL;
}

Animation::Animation(const float length) {
    Animation::length = length;
    duration = 0.0f;
    active = false;
    scale = glm::mat4(1.0f);
    rot = glm::mat4(1.0f);
    trans = glm::mat4(1.0f);
    scaleFunction = NULL;
    rotFunction = NULL;
    transFunction = NULL;
}

Animation::~Animation() {

}

void Animation::reset() {
    active = false;
    spaceDiff = glm::vec3(0);
    scale = glm::mat4(1.0f);
    rot = glm::mat4(1.0f);
    trans = glm::mat4(1.0f);
}

float Animation::getDuration() const {
    return duration;
}

void Animation::setDuration(const float duration) {
    if(active) {
        Animation::duration = duration;
        if (length != 0 && duration > length) {
            active = false;
        }
    }
}

bool Animation::doStep(const float timeDiff, const glm::vec3 & spaceDiff) {
    setDuration(getDuration() + timeDiff);
    Animation::spaceDiff += spaceDiff;
    if (active) {
        if (scaleFunction != NULL) {
            scale = glm::scale(glm::mat4(1.0f), transFunction(duration/length, Animation::spaceDiff, scaleAmpl));
        }
        if (rotFunction != NULL) {
            rot = rotFunction(duration/length, Animation::spaceDiff, rotAxis, rotSpeed);
        }
        if (transFunction != NULL) {
            trans = glm::translate(glm::mat4(1.0f), transFunction(duration/length, Animation::spaceDiff, transAmpl));
        }
    }
    return active;
}

const glm::mat4 & Animation::getScale() const{
    return scale;
}

const glm::mat4 & Animation::getRotation() const{
    return rot;
}

const glm::mat4 & Animation::getTranslation() const{
    return trans;
}

const glm::vec3 Animation::linearTime(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & amplitude){
    return glm::vec3(timeDiff * amplitude);
}
const glm::vec3 Animation::linearTime2p(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & amplitude){
    return glm::vec3(abs(timeDiff - 0.5f) * 2 * amplitude);
}

const glm::mat4 Animation::linearRotXSpace(const float timeDiff, const glm::vec3 & spaceDiff, glm::vec3 & rotAxis, float rotSpeed){
    return glm::rotate(glm::mat4(1.0f), spaceDiff[0] * rotSpeed, glm::vec3(0.0f, 0.0f, -1.0f));
}
