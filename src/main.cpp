/// Include standard headers
#include <cstdlib>
#include <cstdio>
#include <array>
#include <unistd.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "base/shader.h"
#include "base/texture.h"
#include "ball/ball.h"
#include "block/block.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#define INITIAL_SCR_RES_X 1366
#define INITIAL_SCR_RES_Y 768
int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow *window = glfwCreateWindow( INITIAL_SCR_RES_X, INITIAL_SCR_RES_Y, "Simley Wars - a smiple openGL game by Jakob Möderl", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("shader/TransformVertexShader.vertexshader", "shader/TextureFragmentShader.fragmentshader");
    // Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
    GLuint textureBall = loadTexture("pics/ball.tga");
    GLuint textureStone = loadTexture("pics/StoneBlock.tga");

    Block block=Block();
    block.reflection=glm::vec3(1.0f);
	block.textureID = TextureID;
	block.texture = textureStone;
	block.matrixID = MatrixID;
    block.setSize(2.0f, 1.0f, -2.0f);
	block.setPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
    block.setDrawEnable(true);

    Ball ball=Ball();
    ball.reflection=glm::vec3(1.0f);
    ball.textureID = TextureID;
    ball.texture = textureBall;
    ball.matrixID = MatrixID;
    ball.setRadius(.3f);
    ball.setPosition(glm::vec3(+3.4f, -.95f, -0.5f));
    ball.setSpeed(glm::vec3(-1.0f, 0.3f, 0.0f));
    ball.setDrawEnable(true);
    ball.setRollingEnabled(true);

    Ball ball2=Ball();
    ball2.textureID = TextureID;
    ball2.texture = textureBall;
    ball2.matrixID = MatrixID;
    ball2.setRadius(.2f);
    ball2.setPosition(glm::vec3(+3.0f, 0.9f, -0.2f));
    ball2.setSpeed(glm::vec3(0.0f));
    ball2.setDrawEnable(true);
    ball2.setRollingEnabled(false);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (GLfloat)INITIAL_SCR_RES_X / (GLfloat)INITIAL_SCR_RES_Y, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
			glm::vec3(0, -2, 7), // Camera is at (4,3,3), in World Space
			glm::vec3(0.0f,0.0f,0.0f), // and looks at the origin
			glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
	int i=0;
	bool collisionBall=false;
    bool lastCollisionBall=false;
    bool collisionBlock=false;
    bool lastCollisionBlock=false;
	do{
        collisionBlock=ball.checkCollision(block);
        if(collisionBlock){
            ball.doCollisionBounce(block);
        }
        if(collisionBlock!=lastCollisionBlock){
            printf("%s\n", collisionBlock ? "collision with block!": "No collision with block");
            lastCollisionBlock = collisionBlock;
        }
        collisionBall=ball.checkCollision(ball2);
        if(collisionBall!=lastCollisionBall) {
            printf("%s\n", collisionBall ? "collision with ball!" : "No collision with ball");
            lastCollisionBall = collisionBall;
        }

        ball.move(0.01f);
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		block.draw(View, Projection);
		ball.draw(View, Projection);
        ball2.draw(View, Projection);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

        usleep(10000);


	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

