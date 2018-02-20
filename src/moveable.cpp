#include "moveable.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Moveable::Moveable(void)
{
	this->speed={0,0,0};
	this->speedMax={10,10,10};
}


Moveable::~Moveable(void)
{
}

//moves the object depending on the time since the last move
void Moveable::move(GLfloat time){
	setSpeed(speed + acceleration*time);
	setTranslation(glm::translate(translation, speed*time));
}

glm::vec3 Moveable::getSpeed()
{
    return speed;
}
//Sets the x speed, if the x speed is greater then the max speed value it is set to max speed value
void Moveable::setSpeed(glm::vec3 speed)
{
	this->speed=glm::clamp(speed, speedMax, -speedMax); //keep speed in bounds
}

glm::vec3 Moveable::getAcceleration() {
    return this->acceleration;
}
//Sets the y speed, if the y speed is greater then the max speed value it is set to max speed value
void Moveable::setAcceleration(glm::vec3 acceleration)
{
	this->acceleration = acceleration;
}

glm::vec3 Moveable::getSpeedMax()
{
    return this->speedMax;
}
void Moveable::setSpeedMax(glm::vec3 speedMax)
{
	this->speedMax = speedMax;
}