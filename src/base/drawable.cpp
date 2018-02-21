#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "drawable.h"

//standerd konstruktor
Drawable::Drawable()
{
	posVec = glm::vec3(0.0f);
    rotMat = glm::mat4(1.0f);
    scaleMat = glm::scale(glm::mat4(1.0), glm::vec3(1.0));
    modelMat = glm::mat4(1.0f);
	active = true;
    updateModelMat = true;

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
    if(updateModelMat){
        modelMat = glm::translate(rotMat*scaleMat, posVec);
        updateModelMat = false;
    }
    return modelMat;
}


const glm::vec3 & Drawable::getPosition() const {
    return posVec;
}

void Drawable::setPosition(const glm::vec3 & pos) {
    this->posVec = pos;
    updateModelMat = true;
}

const glm::mat4 & Drawable::getRotation() const{
    return this->rotMat;
}

void Drawable::setRotation(const glm::mat4 & rot) {
    this->rotMat = rot;
    updateModelMat = true;
}

const glm::mat4 & Drawable::getScaling() const{
    return this->scaleMat;
}

void Drawable::setScaling(const glm::mat4 & scale) {
    this->scaleMat = scale;
    updateModelMat = true;
}

//returns if the object is active
bool Drawable::isActive() const{
	return active;
}

void Drawable::setActive(const bool active){
    this->active = active;
}


GLuint Drawable::getTexture() const
{
    return texture;
}

void Drawable::setTexture(const GLuint texture)
{
    this->texture = texture;
}

GLuint Drawable::getTextureID() const
{
    return textureID;
}

void Drawable::setTextureID(const GLuint textureID)
{
    this->textureID = textureID;
}

GLuint Drawable::getMatrixID() const
{
    return matrixID;
}

void Drawable::setMatrixID(const GLuint matrixID)
{
    this->matrixID = matrixID;
}
