#include "ball/enemy.h"


Enemy::Enemy(void)
{
	setRadius(0.38f);
    startPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    startSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
    boundUpper = glm::vec3(1.0f, 2.0f, 2.0f);
    boundLower = -boundUpper;

    reset();
}


Enemy::~Enemy(void)
{
}

void Enemy::reset() {
    speed = startSpeed;
    setPosition(startPosition);
    rollingAnimation.reset();
}

void Enemy::move(GLfloat time) {
    Ball::move(time);
    //check x bounds
    if(this->getPosition()[0] > boundUpper[0]){
        setPositionX(boundUpper[0]);
        setSpeedX(-speed[0]);
    } else if(this->getPosition()[0] < boundLower[0]){
        setPositionX(boundLower[0]);
        setSpeedX(-speed[0]);
    }

    //check y bounds
    if(this->getPosition()[1] > boundUpper[1]){
        setPositionY(boundUpper[1]);
        setSpeedY(-speed[1]);
    } else if(this->getPosition()[1] < boundLower[1]){
        setPositionY(boundLower[1]);
        setSpeedY(-speed[1]);
    }

    //check z bounds
    if(this->getPosition()[2] > boundUpper[2]){
        setPositionZ(boundUpper[2]);
        setSpeedZ(-speed[2]);
    } else if(this->getPosition()[2] < boundLower[2]){
        setPositionZ(boundLower[2]);
        setSpeedZ(-speed[2]);
    }
}
