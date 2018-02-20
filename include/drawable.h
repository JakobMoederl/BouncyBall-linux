#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Drawable
{
public:
	Drawable();
	~Drawable(void);

	//abstract method to draw the object
	virtual void draw() = 0;

	//returns the x value of the object
	GLfloat getX();
	//returns the y value of the object
	GLfloat getY();
	//returns the layer (z value, low is in front, hight means in the background)
	GLfloat getLayer();
	//returns the texture (main texture, if the objects needs more textures it has to store them by itself)
	GLuint getTexture(void);
	//returns true if the object is activated
	bool isActive(void);

	//sets the x value of the object
	virtual void setX(GLfloat x);
	//sets the y value of the object
	virtual void setY(GLfloat y);
	//sets the layer (z value) of the object
	void setLayer(GLfloat layer);
	//sets the texture
	void setTexture(GLuint texture);
	//sets if the object is activated or not
	void setActive(bool active);
protected:
	// x value of the object
	GLfloat x;
	//y value of the object
	GLfloat y;
	//z value (layer) of the object
	GLfloat layer;

	//falg which indicats if the object is activated or not
	bool active;


    //vertexes array to draw.
	GLuint vertexArraySize;
    GLuint vertexArrayID;

	//uv coordinates buffer (texture)
	GLuint uvArraySize;
	GLuint uvArrayID;

	//model position matrix (rotation and translation relative to world zero)
	GLuint Model;

	//texture ID
	GLuint texture;
};

#endif