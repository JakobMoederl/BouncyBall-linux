#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

class Drawable
{
public:
	Drawable();
	~Drawable(void);

	//abstract method to draw the object
	virtual void draw() = 0;

    //calculate and return the model matrix
    glm::mat4 getModel();
    //translation matrix getter and setter
    glm::mat4 getTranslation();
    void setTranslation(glm::mat4 trans);
    //rotation matrix getter and setter
    glm::mat4 getRotation();
    void setRotation(glm::mat4 rot);
    //scaling matrix getter and setter
    glm::mat4 getScaling();
    void setScaling(glm::mat4 scale);


	GLuint getTexture(void);
    void setTexture(GLuint texture);

	//returns true if the object is activated
	bool isActive(void);
	//sets if the object is activated or not
	void setActive(bool active);
protected:
    glm::mat4 translation;
    glm::mat4 rotation;
    glm::mat4 scaling;
	//flag which indicates if the object is activated or not
	bool active;


    //vertexes array to draw.
	GLuint vertexArraySize;
    GLuint vertexArrayID;
    GLuint vertexBuffer;

	//uv coordinates buffer (texture)
	GLuint uvArraySize;
	GLuint uvArrayID;
    GLuint uvBuffer;

	//texture ID
	GLuint texture;
};

#endif