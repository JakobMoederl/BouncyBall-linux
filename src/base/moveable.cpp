#include "algorithm"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "moveable.h"

Moveable::Moveable(void)
{
	this->speed=glm::vec3(0,0,0);
	this->speedMax=glm::vec3(10,10,10);
	this->acceleration = glm::vec3(0, 0, 0);
}


Moveable::~Moveable(void)
{
}

//moves the object depending on the time since the last move
void Moveable::move(GLfloat time){
	setSpeed(speed + acceleration*time);
	setPosition(getPosition() + speed*time);
}

const glm::vec3 & Moveable::getSpeed() const
{
    return speed;
}
//Sets the x speed, if the x speed is greater then the max speed value it is set to max speed value
void Moveable::setSpeed(const glm::vec3 & speed)
{
	this->speed=glm::clamp(speed, -speedMax, speedMax); //keep speed in bounds
}

const glm::vec3 & Moveable::getAcceleration() const{
    return this->acceleration;
}
//Sets the y speed, if the y speed is greater then the max speed value it is set to max speed value
void Moveable::setAcceleration(const glm::vec3 & acceleration)
{
	this->acceleration = acceleration;
}

const glm::vec3 & Moveable::getSpeedMax() const
{
    return this->speedMax;
}
void Moveable::setSpeedMax(const glm::vec3 & speedMax)
{
	this->speedMax = speedMax;
}

const GLfloat Moveable::getSpeedX() const {
    return speed[0];
}

const GLfloat Moveable::getSpeedY() const {
    return speed[1];
}

const GLfloat Moveable::getSpeedZ() const {
    return speed[2];
}

void Moveable::setSpeedX(GLfloat speedX) {
    speed[0] = std::clamp(speedX, -speedMax[0], speedMax[0]);
}

void Moveable::setSpeedY(GLfloat speedY) {
    speed[1] = std::clamp(speedY, -speedMax[1], speedMax[1]);
}

void Moveable::setSpeedZ(GLfloat speedZ) {
    speed[2] = std::clamp(speedZ, -speedMax[2], speedMax[2]);
}
