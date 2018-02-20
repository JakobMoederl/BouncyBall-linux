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
	const glm::mat4 & getModel();
    //position matrix getter and setter
	const glm::vec3 & getPosition() const;
	void setPosition(const glm::vec3 &posVec);
    //helper function for collision testing
    virtual const glm::vec3 & getCenter() const = 0;
    //rotation matrix getter and setter
    const glm::mat4 & getRotation() const;
    void setRotation(const glm::mat4 & rot);
    //scaling matrix getter and setter
    const glm::mat4 & getScaling() const;
    void setScaling(const glm::mat4 & scale);

	GLuint getTexture(void) const;
	void setTexture(const GLuint texture);
	GLuint getTextureID(void) const;
	void setTextureID(const GLuint textureID);

	GLuint getMatrixID(void) const;
	void setMatrixID(const GLuint matrixID);
	//returns true if the object is activated
	bool isActive(void) const;
	//sets if the object is activated or not
	void setActive(const bool active);

protected:
    glm::vec3 posVec;
public:

protected:
	glm::mat4 rotMat;
    glm::mat4 scaleMat;
	glm::mat4 modelMat;

	glm::mat4 mvp;
	//flag which indicates if the object is activated or not
	bool active;
	bool updateModelMat;

    //vertexes array to draw.
	GLuint vertexArraySize;
    GLuint vertexArrayID;
    GLuint vertexBuffer;

	//uv coordinates buffer (texture)
	GLuint uvArraySize;
	GLuint uvArrayID;
    GLuint uvBuffer;

	//texture reference
	GLuint texture;
	//texture ID for shader program
	GLuint textureID;
	//mvp ID for shader program
	GLuint matrixID;
};

#endif