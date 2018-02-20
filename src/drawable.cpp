#include "drawable.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//standerd konstruktor
Drawable::Drawable()
{
	translation = glm::translate(glm::mat4(1.0), glm::vec3(0.0f));
    rotation = glm::rotate(glm::mat4(1.0), 0.0f, glm::vec3(0.0f));
    scaling = glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	active = true;
}

//destruktor
Drawable::~Drawable(void)
{
}

glm::mat4 Drawable::getModel(){
    return translation * rotation * scaling;
}

glm::mat4 Drawable::getTranslation() {
    return translation;
}

void Drawable::setTranslation(glm::mat4 trans) {
    this->translation = trans;
}

glm::mat4 Drawable::getRotation() {
    return this->rotation;
}

void Drawable::setRotation(glm::mat4 rot) {
    this->rotation = rot;
}

glm::mat4 Drawable::getScaling() {
    return this->scaling;
}

void Drawable::setScaling(glm::mat4 scale) {
    this->scaling = scale;
}

//returns if the object is active
bool Drawable::isActive(){
	return active;
}

void Drawable::setActive(bool active){
    this->active = active;
}


GLuint Drawable::getTexture(void)
{
	return texture;
}

void Drawable::setTexture(GLuint texture)
{
	this->texture = texture;
}