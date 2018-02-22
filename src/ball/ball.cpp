

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
    setPosition(glm::vec3(0.0f));
	onFloor = false;
    floorBlock = NULL;
    setDrawEnable(true);
    reflection = glm::vec3(0.8f, 0.6f, 0.0f);
    lastPos = getPosition();
	setRadius(0.3f);

    rollingAnimation = AnimationRot(0, 1/radius);
    rollingAnimation.active = true;

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
			1, 1,
			0, 0,
			1, 0,
			1, 1,
			0, 1,
			0, 0
	};

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), &uvBufferData[0], GL_STATIC_DRAW);
}

//moves the ball (with rotation) and looks if it is still on a floor
void Ball::move(const GLfloat time){
    lastPos = getPosition();
	Moveable::move(time);
    rollingAnimation.doStep((getPosition() - lastPos)[0]);
    updateModel = true;
	if(isOnFloor()
       && (getPosition()[0] < floorBlock->getPosition()[0] || getPosition()[0] > floorBlock->getPosition()[0] + floorBlock->getSize()[0])){
		this->onFloor = false;
	}
}

bool Ball::checkCollision(const Block & object) const{
    static glm::vec3 p;
    //p = distance between center of ball nearest box edge
    p = glm::clamp(this->getCenter() - object.getCenter(), -glm::abs(object.getSize()/2.0f), glm::abs(object.getSize()/2.0f));

    //p = vector between closest point and center of ball
    p = (this->getCenter() - (object.getCenter() + p));
    p[2] = 0; //ignore z component for detection
    //if the distance is smaller than the radius of the ball we have a collision
    return glm::length2(p) < pow(getRadius(),2);
}


bool Ball::checkCollision(const Ball &object) const {
    static glm::vec3 p;
    p = getCenter() - object.getCenter();
    //ignore z component for collision detection of balls
    p[2] = 0;
    //length 2 returns the square of the length, so to compare it we need to square the minimum distance too
    return glm::length2(p) < pow(this->getRadius() + object.getRadius(),2);
}


void Ball::doCollisionBounce(Block &block) {
    enum CollisionEdge collisionEdge = getCollisionEdge(block);
    bounceOffEdge(collisionEdge, block);
}

enum CollisionEdge Ball::getCollisionEdge(const Block &block) {
    enum CollisionEdge collisionEdge = COL_NONE;
    glm::vec3 edge;
    glm::vec3 speedDiff;
    glm::vec3 ballCenter = getCenter(); //could save syscalls, but maybe the compiler optimizes it anyways
    glm::vec3 blockCenter = block.getCenter(); //could save syscalls, but maybe the compiler optimizes it anyways

    //detect collision edge
    //if x ball center < x block center --> collision is on the left side
    if(ballCenter[0] < blockCenter[0]){
        //if ball y < block y --> collision on lower left quadrant
        if(ballCenter[1] < blockCenter[1]) {
            //collision is in the lower left region of the block
            //check if edge, left or lower collisoin
            edge = block.getPosition();
            edge[2] = ballCenter[2];    //ignore z-component for collision
            // ball center x > edge x ==> bottom side collision
            if (ballCenter[0] > edge[0]) {
                collisionEdge = COL_BOTTOM;
            } else if (ballCenter[1] > edge[1]) {
            //ball center y > edge y ==> left side collision
                collisionEdge = COL_LEFT;
            } else {
                collisionEdge = COL_BOTTOM_LEFT;
            }
        }
            // collision upper left quadrant
        else {
            edge = block.getPosition();
            edge[2] = ballCenter[2];
            edge[1] = edge[1] + block.getSize()[1];
            // ball center x > edge x ==> top side collision
            if (ballCenter[0] > edge[0]){
                collisionEdge = COL_TOP;
            } else if(ballCenter[1] < edge[1]) {
                //ball center y < edge y ==> left side collision
                collisionEdge = COL_LEFT;
            } else {
                collisionEdge = COL_TOP_LEFT;
                // center (X) of the ball is right of the edge --> top collision
            }
        }
    }
        //if x ball center > x block center --> collision is on the right side
    else {
        //if ball y < block y --> collision on lower right quadrant
        if(ballCenter[1] < blockCenter[1]){
            //collision is in the lower left region of the block
            //check if edge, left or lower collisoin
            edge = block.getPosition();
            edge[0] = edge[0] + block.getSize()[0];
            edge[2] = ballCenter[2]; 	//ignore z-component for collision
            // ball center x < edge x ==> bottom collision
            if (ballCenter[0] < edge[0]){
                collisionEdge = COL_BOTTOM;
            } else if (ballCenter[1] > edge[1]){
                //ball center y > edge > ==> right side collision
                collisionEdge = COL_RIGHT;
            } else {
                //if none of the above, edge collision
                collisionEdge = COL_BOTTOM_RIGHT;
            }
        }
            // upper right quadrant
        else {
            edge = block.getPosition();
            edge[0] = edge[0] + block.getSize()[0];
            edge[1] = edge[1] + block.getSize()[1];
            edge[2] = ballCenter[2]; 	//ignore z-component for collision
            //ball center x < edge x ==> top collision
            if (ballCenter[0] < edge[0]){
                collisionEdge = COL_TOP;
            } else if (ballCenter[1] < edge[1]){
                //ball center y > edge y ==> right collision
                collisionEdge = COL_RIGHT;
            } else {
                //if none of the above, edge collision
                collisionEdge = COL_TOP_RIGHT;
            }
        }

    }
    return collisionEdge;
}

void Ball::bounceOffEdge(const enum CollisionEdge edgeEnum, Block &block) {
    float anglePos;
    float angleSpeed;
    float totalSpeed;
    glm::vec3 edge;
    glm::vec3 speedDiff = speed - block.getSpeed();
    speedDiff[2] = 0;   //ignore speed z component
    switch(edgeEnum){
        case COL_TOP:
            speed[1] = block.getSpeed()[1] - speedDiff[1]*reflection[1]*block.reflection[1];
            if(speed[1] < 1.5f){
                speed[1] = 0;
                setOnFloor(true, &block);
            }
            setPositionY(radius + block.getPosition()[1] + block.getSize()[1]);
            break;
        case COL_BOTTOM:
            speed[1] = block.getSpeed()[1] -speedDiff[1]*reflection[1]*block.reflection[1];
            setPositionY(block.getPosition()[1] - radius);
            break;
        case COL_LEFT:
            speed[0] = block.getSpeed()[0] - speedDiff[0]*reflection[0]*block.reflection[0];
            setPositionX(block.getPosition()[0] - radius);
            break;
        case COL_RIGHT:
            speed[0] = block.getSpeed()[0] - speedDiff[0]*reflection[0]*block.reflection[0];
            setPositionX(block.getPosition()[0] + block.getSize()[0] + radius);
            break;
        case COL_BOTTOM_LEFT:
        case COL_TOP_LEFT:
        case COL_TOP_RIGHT:
        case COL_BOTTOM_RIGHT:
            //change position to edge of block
            edge = block.getPosition();
            printf("speed before collision: %f\n", glm::length(speed));

            if(edgeEnum == COL_TOP_LEFT || edgeEnum == COL_TOP_RIGHT){
                edge[1] += block.getSize()[1];
            }
            if(edgeEnum == COL_TOP_RIGHT || edgeEnum == COL_BOTTOM_RIGHT){
                edge[0] += block.getSize()[0];
            }

            anglePos = atanf((edge[1] - getPosition()[1]) / (edge[0] - getPosition()[0]));
            if(edge[0] - getPosition()[0] < 0) anglePos += M_PI;    //correct atan fucntion if in 2nd or 3th quadrant
            setPositionX(edge[0] - radius*1.001f * cos(anglePos));
            setPositionY(edge[1] - radius*1.001f * sin(anglePos));

            if(checkCollision(block)) printf("still in collision after position correction\n");
            //calc new speed with angle of reflection = angle of impact (relative to angle between ball and edge)
            angleSpeed = atanf(speedDiff[1] / speedDiff[0]);
            if(speedDiff[0] < 0) angleSpeed += M_PI; //correct the angle if necessary
            angleSpeed = anglePos + M_PI + (anglePos - angleSpeed); //calculate new angle of speed vector
            //calculate total speed
            totalSpeed = glm::length(speedDiff) * (pow(cosf(angleSpeed),2)*reflection[0]*block.reflection[0] + pow(sinf(angleSpeed), 2)*reflection[1]*block.reflection[1]);
            speed[0] = block.getSpeed()[0] + totalSpeed*cosf(angleSpeed);
            speed[1] = block.getSpeed()[1] + totalSpeed*sinf(angleSpeed);

            printf("speed after collision: %f\n", glm::length(speed));
            break;

        default:    //unrecognized edge
            break;
            //do nothing
    }
}

//Sets the radius of the ball
void Ball::setRadius(const GLfloat radius)
{
	this->radius = radius;
    updateModel = true;
    this->rollingAnimation.amplitude = 1/radius;
}

//gets the radius of the ball
GLfloat Ball::getRadius(void) const
{
	return radius;
}

//sets if the ball is on floor or not (and also from where to where the floor is wher the ball is currently on)
void Ball::setOnFloor(bool onFloor, Block * block)
{
	this->onFloor = onFloor;
    this->floorBlock = block;
}

//returns true if the ball is currently on floor
bool Ball::isOnFloor() const
{
	return onFloor;
}


//sets if the rotation is enabled or not
void Ball::setRollingEnabled(bool enabled) {
    this->rollingAnimation.active = enabled;
}

//gets if rotation is enabled for this ball
bool Ball::isRollingEnabled() const{
	return rollingAnimation.active;
}

inline const glm::vec3 &Ball::getCenter() const {
    return getPosition();
}

const glm::mat4 &Ball::getModel() {
    if(updateModel){
		//model  = translation * rotation * scaling of model, rolling animation and death animation. thats a lot of matrixes for each ball.
        model = glm::translate(glm::mat4(1.0f), getPosition()) * rollingAnimation.mat * glm::scale(glm::mat4(1.0f), glm::vec3(radius, radius, 0.0f));
    }
    return model;
}
