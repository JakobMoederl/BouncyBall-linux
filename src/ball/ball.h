#ifndef _BALL_H_
#define _BALL_H_

#include <array>
#include "base/moveable.h"
#include "animation/animation_rot.h"
#include "block/block.h"

#define VERTICES_PER_BALL (1*2*3) //1 side(rectangle) which consists of two triangles with 3 vertices each.
enum CollisionEdge{
	COL_NONE=0, COL_BOTTOM, COL_TOP, COL_LEFT, COL_RIGHT, COL_TOP_LEFT, COL_TOP_RIGHT, COL_BOTTOM_LEFT, COL_BOTTOM_RIGHT
};

class Ball : public Moveable
{
public:
	Ball();
	Ball(const glm::vec3 & position);
	~Ball();

	//standard draw function, override for advanced drawing (animations)
	virtual void draw(const glm::mat4 & view, const glm::mat4 & projection);

	//advanced move function which also calculates the ange the ball has to rotate 
	void move(const GLfloat time) override;

	//check for collision with a ball object
	bool checkCollision(const Block& object) const;
	//returns true if the Ball has a kollision with the other ball
	bool checkCollision(const Ball& object) const;

	//standard bouncy collision.
	void doCollisionBounce(Block& block);
	enum CollisionEdge getCollisionEdge(const Block& block);
	void bounceOffEdge(const enum CollisionEdge edge, Block& block);

	//get the model matrix (for draw function)
	const glm::mat4 & getModel() override;

    //returns the radius if the ball (in units)
    GLfloat getRadius() const;
    void setRadius(const GLfloat radius);

	virtual const glm::vec3 & getCenter() const;
	
	//returns true if the ball is rolling on a block or the bottom of the lvl
	bool isOnFloor() const;
	//sets the onFloor flag in the specified area
	void setOnFloor(const bool onFloor, Block * block);

    bool isRollingEnabled() const;
	void setRollingEnabled(const bool rolling);

    glm::vec3 reflection;
protected:
    virtual void genVertexBufferData();

    AnimationRot rollingAnimation;


    std::array<GLfloat, VERTICES_PER_BALL * 3> vertexBufferData;
	std::array<GLfloat, VERTICES_PER_BALL * 2> uvBufferData;

private:
    //on floor flag
    bool onFloor;
    Block* floorBlock;

	//last x position for angle calculation
	glm::vec3 lastPos;

	//radius
	GLfloat radius;
};

#endif