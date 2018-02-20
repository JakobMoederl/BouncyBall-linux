#ifndef _BALL_H_
#define _BALL_H_

#include <array>
#include "base/moveable.h"
#include "animation/animation_rot.h"

#define VERTICES_PER_BALL (1*2*3) //1 side(rectangle) which consists of two triangles with 3 vertices each.

class Ball : public Moveable
{
public:
	Ball();
	Ball(const glm::vec3 & position);
	~Ball();

	//advanced move function which also calculates the ange the ball has to rotate 
	void move(const GLfloat time) override;

	//returns true if the Ball has a kollision with the other ball
	bool checkCollision(const Ball& object) const;
    //should override to compute on a kollion
    virtual void doCollision(Ball& object) = 0;

	//standart draw funtion, overide for advanced drawing (animations)
	virtual void draw(const glm::mat4 & view, const glm::mat4 & projection);

	const glm::vec3 & getReflection() const;
    void setReflection(const glm::vec3 & reflection);

    //returns the radius if the ball (in units)
    GLfloat getRadius() const;
    void setRadius(const GLfloat radius);

	virtual const glm::vec3 & getCenter() const;
	
	//returns true if the ball is rolling on a block or the bottom of the lvl
	bool isOnFloor() const;
	//sets the onFloor flag in the specified area
	void setOnFloor(const bool onFloor, const glm::vec2 & floorBounds);

    bool isRollingEnabled() const;
	void setRollingEnabled(const bool rolling);

protected:
	void genVertexBufferData();

    AnimationRot rolling;

	glm::vec3 reflection;

	//last x position for angle calculation
	GLfloat x_last;
	//angle
	bool rotationEnabled;
	//radius
	GLfloat radius;

	//on floor flag
	bool onFloor;
	glm::vec2 floorBounds;

    std::array<GLfloat, VERTICES_PER_BALL * 3> vertexBufferData;
	std::array<GLfloat, VERTICES_PER_BALL * 2> uvBufferData;
};

#endif