#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <array>

#include "base/moveable.h"
#include "ball/ball.h"

#define VERTICES_PER_CUBE (6*2*3)		//6 sides * 2 triangles/side * 3 vertices/triangle

class Block : public Moveable
{
public:
	Block();
	Block(const GLfloat x, const GLfloat y, const GLfloat width, const GLfloat height);
	~Block();

	//returns true if there is a kollision with the Ball
    // standert methode of the block
	virtual void draw(const glm::mat4 & view, const glm::mat4 & projection);

	//check for collision with a ball object
	bool checkCollision(const Ball& object) const;
    //if a collision occurs, calculate its effect --> depends on block type either player dies or
    virtual void doCollision(Ball& object) = 0;

    //returns the width of the block
    GLfloat getWidth() const;
	//sets the width of the block
	void setWidth(const GLfloat width);
    //returns the height of the block
    GLfloat getHeight() const;
	//sets the height of the block
	void setHeight(const GLfloat height);
    GLfloat getDepth() const;
	void setDepth(const GLfloat depth);
    //return the center of the block, mostly useful for collision detection
	virtual const glm::vec3 & getCenter() const;

    const glm::vec3 & getReflection() const;
	void setReflection(const glm::vec3 & reflection);

protected:
	void genVertexBufferData();
	//width of the block
	GLfloat width;
	//height of the block
	GLfloat height;
	//deapth of the block
	GLfloat depth;

	glm::vec3 reflection;

	std::array<GLfloat, VERTICES_PER_CUBE * 3> vertexBufferData;		//x vertices * 3 coordinates/vertex
	std::array<GLfloat, VERTICES_PER_CUBE * 2> uvBufferData;			//x vertices * 2 coordinates/vertex
};

#endif