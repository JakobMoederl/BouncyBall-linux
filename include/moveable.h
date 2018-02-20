#ifndef _MOVEABLE_H_
#define _MOVEABLE_H_

#include <glm/glm.hpp>

#include "drawable.h"
class Moveable : public Drawable
{
public:
	Moveable(void);
	~Moveable(void);

	//moves the object depending on the time difference
	void move(GLfloat time);

	//sets the speed in x direction
    glm::vec3 getSpeed();
	void setSpeed(glm::vec3 speed);
	//sets the maximum speed in x direction
    glm::vec3 getSpeedMax();
	void setSpeedMax(glm::vec3 speedMax);
	//sets the acceleration
    glm::vec3 getAcceleration();
	void setAcceleration(glm::vec3 acceleration);


protected:
	glm::vec3 speed;
	glm::vec3 speedMax;
	glm::vec3 acceleration;
	
};

#endif