

#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include "ball.h"

//standardkonstrucktor
Ball::Ball()
{
	onFloor = false;
    setDrawEnable(true);
	floorBounds = glm::vec2(0.0f);
    reflection = glm::vec3(0.8f, 0.6f, 0.0f);

	x_last = getPosition()[0];
	setRadius(0.3f);

	rolling = AnimationRot(0.0f, 1/radius);

    genVertexBufferData();
}

//General constructor (sets also x and y position of the ball)
Ball::Ball(const glm::vec3 & pos): Ball(){
    setPosition(pos);
}

//destructor
Ball::~Ball()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);

	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteVertexArrays(1, &uvArrayID);
}

//draw function, draws the ball at the right position and angel
void Ball::draw(const glm::mat4 & view, const glm::mat4 & projection){
    if(!isDrawEnabled()){
        return;
    }
    //perform animation on vertex before MVP matrix;
    static glm::mat4 mvp;
    mvp = projection * view * getModel();
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
    glDrawArrays(GL_TRIANGLES, 0, VERTICES_PER_BALL); // 12*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Ball::genVertexBufferData() {


	glBindVertexArray(vertexArrayID);
	vertexBufferData={
			//front side
			-1.0f, -1.0f, 0,
			1.0f, 1.0f, 0,
            -1.0f, 1.0f, 0,
            -1.0f, -1.0f, 0,
			1.0f, -1.0f, 0,
			1.0f, 1.0f, 0,
	};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), &vertexBufferData[0], GL_STATIC_DRAW);


	glBindVertexArray(uvArrayID);

	uvBufferData={
			0, 0,
			1, 1,
			0, 1,
			0, 0,
			1, 0,
			1, 1
	};

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), &uvBufferData[0], GL_STATIC_DRAW);
}

//moves the ball (with rotation) and looks if it is still on a floor
void Ball::move(const GLfloat time){
	Moveable::move(time);
	rolling.doStep(getPosition()[0] - x_last);
    updateModel = true;
    x_last = getPosition()[0];
	if(isOnFloor() && (getPosition()[0] < floorBounds[0] || getPosition()[0] > floorBounds[1])){
		this->onFloor = false;
	}
}

//sets the reflection factor for bouncing against a vertical wall (horizontal speed)
void Ball::setReflection(const glm::vec3 & reflection)
{
	this->reflection = reflection;
}

//Sets the radius of the ball
void Ball::setRadius(const GLfloat radius)
{
	this->radius = radius;
    updateModel = true;
    this->rolling.setAmplitude(1/radius);
}

//get reflection factor of the ball
const glm::vec3 & Ball::getReflection() const
{
	return reflection;
}


//gets the radius of the ball
GLfloat Ball::getRadius(void) const
{
	return radius;
}

//sets if the ball is on floor or not (and also from where to where the floor is wher the ball is currently on)
void Ball::setOnFloor(bool onFloor, const glm::vec2 & floorBounds)
{
	this->onFloor = onFloor;
    this->floorBounds = floorBounds;
}

//returns true if the ball is currently on floor
bool Ball::isOnFloor() const
{
	return onFloor;
}


//sets if the rotation is enabled or not
void Ball::setRollingEnabled(bool enabled) {
    this->rolling.setActive(enabled);
}

//gets if rotation is enabled for this ball
bool Ball::isRollingEnabled() const{
	return rolling.isActive();
}

bool Ball::checkCollision(const Ball &object) const {
    static glm::vec3 p;
    p = getCenter() - object.getCenter();
    //ignore z component for collision detection of balls
    p[2] = 0;
    //length 2 returns the square of the length, so to compare it we need to square the minimum distance too
    return glm::length2(p) < pow(this->getRadius() + object.getRadius(),2);
}

inline const glm::vec3 &Ball::getCenter() const {
    return getPosition();
}

float Ball::getAngle() const {
    return rolling.getDuration();
}

const glm::mat4 &Ball::getModel() {
    if(updateModel){
		//model  = translation * rotation * scaling
        model = glm::translate(glm::mat4(1.0f), getPosition()) * rolling.getMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(radius, radius, 0.0f));
    }
    return model;
}
