#include "block.h"

#include <math.h>
#include "ball.h"
#include "game.h"

//Standartkonstrucktor
Block::Block(void)
{
	vertexArraySize=6*2*3; //6 sides, with two triangles each with 3 vertexes per triangle

	width = 1;
	height = 1;
	kollisionsType = HT_NO_KOLLISION;
	reflection_x = 1.0f;
	reflection_y = 1.0f;
	depth = 1;
	genVertexBufferData();
}

//destrucktor
Block::~Block(void)
{
}

//draws the block
void Block::draw(){
	if(!active){
		return;
	}
	extern Game game;
	glBindTexture(GL_TEXTURE_2D,texture);

}

void Block::genVertexBufferData() {
	vertexBufferData={
			//front side
			0, 0, 0,
			width, height, 0,
			0, height, 0,
			0, 0, 0,
			width, 0, 0,
			width, height, 0,
			//left side
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

	uvBufferData={
			0, 0,
			width, height,
			0, height,
			0, 0,
			width, 0,
			width, height,
			//left side
			width, 0,
			width, height,
			width, height,
			width, 0,
			width, 0,
			width, height,
			//back side
			width, 0,
			0, height,
			width, height,
			width, 0,
			0, 0,
			0, height,
			//right side
			0, 0,
			0, height,
			0, height,
			0, 0,
			0, 0,
			0, height,
			//top side
			0, height,
			width, height,
			0, height,
			0, height,
			width, height,
			width, height,
			//bottom side
			0, 0,
			width, 0,
			0, 0,
			0, 0,
			width, 0,
			width, 0,
	};

    glGenBuffers(1, &vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

    glGenBuffers(1, &uvArrayID);
    glBindBuffer(GL_ARRAY_BUFFER, uvArrayID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);
}

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

//Sets the width od the block
void Block::setWidth(GLfloat width){
	this->width = width;
}

//Sets the height of the block
void Block::setHeight(GLfloat height){
	this->height = height;
}

//Sets the height of the block
void Block::setDepth(GLfloat depth){
	this->depth = depth;
}

//setst the reflection if a ball bounces against the vertical outlines of the block, default is 1)
void Block::setReflectionX(GLfloat reflection_x){
	this->reflection_x = reflection_x;
}

//setst the reflection if a ball bounces against the vertical outlines of the block, default is 1)
void Block::setReflectionY(GLfloat reflection_y){
	this->reflection_y = reflection_y;
}

//returns the width of the block
GLfloat Block::getWidth(){
	return width;
}

GLfloat Block::getHeight(){
	return height;
}

GLfloat Block::getDepth(){
	return depth;
}

GLfloat Block::getReflectionX(){
	return reflection_x;
}

GLfloat Block::getReflectionY(){
	return reflection_y;
}

HittingType Block::getKollisionType(){
	return kollisionsType;
}


