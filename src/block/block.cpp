#include <GL/glew.h>
#include "block.h"

//Standartkonstrucktor
Block::Block(void)
{
	vertexArraySize=6*2*3; //6 sides, with two triangles each with 3 vertexes per triangle

	width = 1;
	height = 1;
    depth = 1;

	reflection = glm::vec3(1.0f);

	genVertexBufferData();
}

//destrucktor
Block::~Block(void)
{
}

//draws the block
void Block::draw(const glm::mat4 & view, const glm::mat4 & projection){
	if(!active){
		return;
	}
    this->mvp = projection * view * getModel();
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(textureID, 0);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size : U+V => 2
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, vertexArraySize); // 12*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Block::genVertexBufferData() {


	glBindVertexArray(vertexArrayID);

	vertexBufferData={
			//front side
			0, 0, 0,
			width, height, 0,
			0, height, 0,
			0, 0, 0,
			width, 0, 0,
			width, height, 0,
			//right side
			width, 0, 0,
			width, height, depth,
			width, height, 0,
			width, 0, 0,
			width, 0, depth,
			width, height, depth,
			//back side
			width, 0, depth,
			0, height, depth,
			width, height, depth,
			width, 0, depth,
			0, 0, depth,
			0, height, depth,
			//right side
			0, 0, depth,
			0, height, 0,
			0, height, depth,
			0, 0, depth,
			0, 0, 0,
			0, height, 0,
			//top side
			0, height, 0,
			width, height, depth,
			0, height, depth,
			0, height, 0,
			width, height, 0,
			width, height, depth,
			//bottom side
			0, 0, depth,
			width, 0, 0,
			0, 0, 0,
			0, 0, depth,
			width, 0, depth,
			width, 0, 0
			};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), &vertexBufferData[0], GL_STATIC_DRAW);


	glBindVertexArray(uvArrayID);

	uvBufferData={
            //front side
            0, 0,
            width, height,
            0, height,
            0, 0,
            width, 0,
            width, height,
            //right side
            0, 0,
            depth, height,
            0, height,
            0, 0,
            depth, 0,
            depth, height,
            //back side
            0, 0,
            width, height,
            0, height,
            0, 0,
            width, 0,
            width, height,
            //left side
            0, 0,
            depth, height,
            0, height,
            0, 0,
            depth, 0,
            depth, height,
            //top side
            0, 0,
            width, depth,
            0, depth,
            0, 0,
            width, 0,
            width, depth,
            //bottom side
            0, 0,
            width, depth,
            0, depth,
            0, 0,
            width, 0,
            width, depth,
	};

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), &uvBufferData[0], GL_STATIC_DRAW);
}

bool Block::checkCollision(const Ball & object) const{
    //p = distance between center of ball and box
    static glm::vec3 p = object.getCenter() - this->getCenter();
    //p = closest point of box to center of ball (relative to box center)
    p = glm::clamp(p, -glm::vec3(width, height, depth)/2.0f, glm::vec3(width, height, depth)/2.0f);
    //p = vector between closest point and center of ball
	p = (object.getCenter() - (this->getCenter() + p));
	//calculate distance between ball and the closest point;
    static GLfloat distance = glm::length(p);
    //if the distance is smaller than the radius of the ball we have a collision
    return distance < object.getRadius();
}

/*
//returns true if there is any kollision (if so the kollisions type value is set)
bool Block::getKollisionEdge(Ball& object){
	if(!(active && object.isActive())){
		kollisionsType = HT_NO_KOLLISION;
		return false;
	}
	
	//top and bottom
	if(object.getX() > x && object.getX() < (x + width) && object.getSpeedY() != 0 ){
		if(object.getY() + object.getRadius() > y && object.getY() - object.getRadius() < y + height){
			if(object.getSpeedY() > 0){
				kollisionsType = HT_BOTTOM;
				return true;
			} else {
				kollisionsType = HT_TOP;
				return true;
			}
		}
	}

	//left and right
	if(object.getY() > y && object.getY() < (y + height) && object.getSpeedX() != 0){
		if( (object.getX() + object.getRadius()) > x &&  (object.getX() - object.getRadius()) < (x + width)){
			if(object.getSpeedX() > 0.0f){
				kollisionsType = HT_LEFT;
				return true;
			} else {
				kollisionsType = HT_RIGHT;
				return true;
			}
		}
	}
	
	return false;
}

//returns true if there is a collision at the corners
bool Block::getKollisionCorner(Ball& object){
	if(!(active && object.isActive())){
		return false;
	}

	//Corners
	if(sqrtf(powf(x - object.getX(), 2) + powf(y - object.getY(), 2)) < (object.getRadius() - 0.01f)){
		kollisionsType = HT_LOWER_LEFT_CORNER;
		return true;
	} else if(sqrtf(powf(x - object.getX(), 2) + powf(y + height - object.getY(), 2)) < (object.getRadius() - 0.01f)){
		kollisionsType = HT_UPPER_LEFT_CORNER;
		return true;
	} else if(sqrtf(powf(x + width - object.getX(), 2) + powf(y + height - object.getY(), 2)) < (object.getRadius() - 0.01f)){
		kollisionsType = HT_UPPER_RIGHT_CORNER;
		return true;
	} else if(sqrtf(powf(x + width - object.getX(), 2) + powf(y - object.getY(), 2)) < (object.getRadius() - 0.01f)){
		kollisionsType = HT_LOWER_RIGHT_CORNER;
		return true;
	}
	return false;
}
 */

inline const glm::vec3 & Block::getCenter() const {
    return (this->posVec + glm::vec3(width, height, depth)/2.0f);
}

//Sets the width od the block
void Block::setWidth(const GLfloat width){
	this->width = width;
	genVertexBufferData();
}

//Sets the height of the block
void Block::setHeight(const GLfloat height){
	this->height = height;
	genVertexBufferData();
}

//Sets the height of the block
void Block::setDepth(const GLfloat depth){
	this->depth = depth;
	genVertexBufferData();
}

void Block::setReflection(const glm::vec3 &reflection)
{
	Block::reflection = reflection;
}

//returns the width of the block
GLfloat Block::getWidth() const
{
	return width;
}

GLfloat Block::getHeight() const
{
	return height;
}

GLfloat Block::getDepth() const
{
	return depth;
}

const glm::vec3 & Block::getReflection() const
{
	return reflection;
}

void Block::setSize(const GLfloat width, const GLfloat height, const GLfloat depth) {
	Block::width = width;
	Block::height = height;
	Block::depth = depth;
	genVertexBufferData();
}

void Block::setSize(glm::vec3 size) {
	setSize(size[0], size[1], size[2]);
}

