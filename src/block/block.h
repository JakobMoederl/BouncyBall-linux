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
	~Block();

	//returns true if there is a kollision with the Ball
    // standert methode of the block
	virtual void draw(const glm::mat4 & view, const glm::mat4 & projection);

	//check for collision with a ball object
	bool checkCollision(const Ball& object) const;
    //if a collision occurs, calculate its effect --> depends on block type either player dies or
    //virtual void doCollision(Ball& object) = 0;

    void setPosition(const glm::vec3 & post) override;
    //returns the width of the block
    const glm::vec3 & getSize() const;
	void setSize(const GLfloat width, const GLfloat height, const GLfloat depth);
	void setSize(const glm::vec3 & size);
    //return the center of the block, mostly useful for collision detection
	virtual const glm::vec3 & getCenter() const;

    const glm::vec3 & getReflection() const;
	void setReflection(const glm::vec3 & reflection);

protected:
	void genVertexBufferData();
	//width of the block
	glm::vec3 size;
	glm::vec3 center;

	glm::vec3 reflection;

	std::array<GLfloat, VERTICES_PER_CUBE * 3> vertexBufferData;		//x vertices * 3 coordinates/vertex
	std::array<GLfloat, VERTICES_PER_CUBE * 2> uvBufferData;			//x vertices * 2 coordinates/vertex
};

#endif