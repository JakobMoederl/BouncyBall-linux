
#include <math.h>
#include <GL/glew.h>
#include <glm/gtx/norm.hpp>
#include "block.h"

//Standartkonstrucktor
Block::Block(void)
{
	size=glm::vec3(1.0f);
    reflection = glm::vec3(0.0f);
    jump_speed = 10.0f;
	genVertexBufferData();
}

//destrucktor
Block::~Block(void)
{
}

//draws the block
void Block::draw(const glm::mat4 & view, const glm::mat4 & projection){
	if(!isDrawEnabled()){
		return;
	}
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
    glDrawArrays(GL_TRIANGLES, 0, VERTICES_PER_CUBE); // 12*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Block::genVertexBufferData() {


	glBindVertexArray(vertexArrayID);

	vertexBufferData={
			//front side
			0, 0, 0,
			size[0], size[1], 0,
			0, size[1], 0,
			0, 0, 0,
			size[0], 0, 0,
			size[0], size[1], 0,
			//right side
			size[0], 0, 0,
			size[0], size[1], size[2],
			size[0], size[1], 0,
			size[0], 0, 0,
			size[0], 0, size[2],
			size[0], size[1], size[2],
			//back side
			size[0], 0, size[2],
			0, size[1], size[2],
			size[0], size[1], size[2],
			size[0], 0, size[2],
			0, 0, size[2],
			0, size[1], size[2],
			//right side
			0, 0, size[2],
			0, size[1], 0,
			0, size[1], size[2],
			0, 0, size[2],
			0, 0, 0,
			0, size[1], 0,
			//top side
			0, size[1], 0,
			size[0], size[1], size[2],
			0, size[1], size[2],
			0, size[1], 0,
			size[0], size[1], 0,
			size[0], size[1], size[2],
			//bottom side
			0, 0, size[2],
			size[0], 0, 0,
			0, 0, 0,
			0, 0, size[2],
			size[0], 0, size[2],
			size[0], 0, 0
			};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), &vertexBufferData[0], GL_STATIC_DRAW);


	glBindVertexArray(uvArrayID);

	uvBufferData={
            //front side
            0, 0,
            size[0], size[1],
            0, size[1],
            0, 0,
            size[0], 0,
            size[0], size[1],
            //right side
            0, 0,
            size[2], size[1],
            0, size[1],
            0, 0,
            size[2], 0,
            size[2], size[1],
            //back side
            0, 0,
            size[0], size[1],
            0, size[1],
            0, 0,
            size[0], 0,
            size[0], size[1],
            //left side
            0, 0,
            size[2], size[1],
            0, size[1],
            0, 0,
            size[2], 0,
            size[2], size[1],
            //top side
            0, 0,
            size[0], size[2],
            0, size[2],
            0, 0,
            size[0], 0,
            size[0], size[2],
            //bottom side
            0, 0,
            size[0], size[2],
            0, size[2],
            0, 0,
            size[0], 0,
            size[0], size[2],
	};

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), &uvBufferData[0], GL_STATIC_DRAW);
}

inline const glm::vec3 & Block::getCenter() const {
    return center;
}

void Block::setSize(const GLfloat width, const GLfloat height, const GLfloat depth) {
    Block::size = glm::vec3(width, height, depth);
    Block::center = Block::getPosition() + size/2.0f;
	genVertexBufferData();
}

void Block::setSize(const glm::vec3 & size) {
	Block::size = size;
    Block::center = Block::getPosition() + Block::size/2.0f;
    genVertexBufferData();
}

const glm::vec3 &Block::getSize() const {
    return size;
}

void Block::setPosition(const glm::vec3 &post) {
    Drawable::setPosition(post);
    Block::center = Block::getPosition() + Block::size/2.0f;
}

