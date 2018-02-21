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
	virtual void draw(const glm::mat4 &view, const glm::mat4 &projection) = 0;

	//return the model matrix
	virtual const glm::mat4 & getModel();
    //position matrix getter and setter
	const glm::vec3 & getPosition() const;
	virtual void setPosition(const glm::vec3 &posVec);

	virtual bool isDrawEnabled(void) const;
	//sets if the object is activated or not
	virtual void setDrawEnable(const bool active);

    //if set to True the model matrix gets recalculated on the next call of getModel();
    bool updateModel;
    //texture reference
    GLuint texture;
    //texture ID for shader program
    GLuint textureID;
    //mvp ID for shader program
    GLuint matrixID;

protected:
    GLuint vertexArrayID;
    GLuint vertexBuffer;

    //uv coordinates buffer (texture)
    GLuint uvArrayID;
    GLuint uvBuffer;
    glm::mat4 model;

private:
    glm::vec3 posVec;
	//flag which indicates if the object is activated or not
	bool drawEnabled;
};

#endif