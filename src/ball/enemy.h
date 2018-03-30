#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "ball.h"
class Enemy : public Ball
{
public:
	Enemy(void);
	~Enemy(void);

	void move(GLfloat time) override;

	void reset();

    glm::vec3 startSpeed;
    glm::vec3 startPosition;
    glm::vec3 boundUpper;
    glm::vec3 boundLower;

    bool solid;
    bool floating;

};
#endif
