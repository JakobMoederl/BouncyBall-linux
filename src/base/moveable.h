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
	virtual void move(const GLfloat time);

	//sets the speed in x direction
    const glm::vec3 & getSpeed() const;
	void setSpeed(const glm::vec3 & speed);
	//sets the maximum speed in x direction
    const  glm::vec3 & getSpeedMax() const;
	void setSpeedMax(const glm::vec3 & speedMax);
	//sets the acceleration
    const glm::vec3 & getAcceleration() const;
	void setAcceleration(const glm::vec3 & acceleration);


protected:
	glm::vec3 speed;
	glm::vec3 speedMax;
	glm::vec3 acceleration;
};

#endif