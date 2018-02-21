#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "drawable.h"

//standerd konstruktor
Drawable::Drawable()
{
	posVec = glm::vec3(0.0f);
    model = glm::mat4(1.0f);
	drawEnabled = true;
    updateModel = true;

    glGenVertexArrays(1, &vertexArrayID);
    glGenVertexArrays(1, &uvArrayID);

    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &uvBuffer);
}

//destruktor
Drawable::~Drawable()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);

    glDeleteVertexArrays(1, &vertexArrayID);
    glDeleteVertexArrays(1, &uvArrayID);
}

const glm::mat4 & Drawable::getModel(){
    if(updateModel){
        model = glm::translate(glm::mat4(1.0f), posVec);
        updateModel = false;
    }
    return model;
}


const glm::vec3 & Drawable::getPosition() const {
    return posVec;
}

void Drawable::setPosition(const glm::vec3 & pos) {
    this->posVec = pos;
    updateModel = true;
}

//returns if the object is active
bool Drawable::isDrawEnabled() const{
	return drawEnabled;
}

void Drawable::setDrawEnable(const bool active){
    this->drawEnabled = active;
}