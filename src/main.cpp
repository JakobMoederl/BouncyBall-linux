// Programmer: Mihalis Tsoukalos
// Date: Wednesday 04 June 2014
//
// A simple OpenGL program that draws a triangle.

#include <sys/time.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"

Game game;

void exit(int exit_code);
inline GLfloat calcTimeDifference(struct timeval time_new, struct timeval time_old);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod);

int main(int argc, char **argv)
{
    // init GLFW
    if (!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "Smiley Wars - a simple openGL game by Jakob Moederl", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental=true;
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    struct timeval time_old;	//time when game calculations started
    struct timeval time_now;	//tme when game calculations where finished

    GLfloat time_difference;

    game.initFirst();

    gettimeofday(&time_old, NULL);

    while(!glfwWindowShouldClose(window) && !game.isDone()){
        //calculation the time difference since the last calculation
        gettimeofday(&time_now, NULL);
        time_difference = calcTimeDifference(time_now, time_old);

        time_old.tv_sec=time_now.tv_sec;
        time_old.tv_usec=time_now.tv_usec;

        //do the main calculation (check win/loose conditions, check collisions, do animations, draw)
        game.playFrame(time_difference);
        glfwSwapBuffers(window);
        glfwPollEvents();

        gettimeofday(&time_now, NULL);
        time_difference = calcTimeDifference(time_now, time_old);

        if (time_difference < 1/(GLfloat)60) {
            usleep(1000000*(int)(1/(GLfloat)60 - time_difference));
        }

    }
    //game finished, terminate window and exit.
    glfwTerminate();
    return 0;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod){
    if(game.isPause()){
        if ( action == GLFW_KEY_DOWN) {
            switch (key) {
                case GLFW_KEY_P:
                case GLFW_KEY_UP:
                case GLFW_KEY_LEFT:
                case GLFW_KEY_RIGHT:
                case GLFW_KEY_SPACE:
                    game.setPause(false);
                    break;
                default:
                    break;
            }
        }
    } else if (action == GLFW_KEY_DOWN) {
        switch (key) {
            case GLFW_KEY_LEFT:
                game.moveLeft();
                break;
            case GLFW_KEY_RIGHT:
                game.moveRight();
                break;
            case GLFW_KEY_UP:
            case GLFW_KEY_SPACE:
                game.wantJump();
                break;
            default:
                break;
        }

    } else if(action == GLFW_KEY_UP){
        if(key == GLFW_KEY_LEFT && game.isMovingLeft()){
            game.moveStop();
        } else if(key == GLFW_KEY_RIGHT && game.isMovingRight()){
            game.moveStop();
        } else if(key == GLFW_KEY_SPACE || key == GLFW_KEY_UP){
            game.setWantJump(false);
        }
    }
}

inline GLfloat calcTimeDifference(struct timeval time_new, struct timeval time_old){
    GLfloat time_difference;
    if(time_new.tv_sec == time_old.tv_sec){
        time_difference  =  ((GLfloat)time_new.tv_usec-(GLfloat)time_old.tv_usec)/1000000;
    } else if(time_new.tv_sec == time_old.tv_sec +1){
        time_difference = (GLfloat)1 + ((GLfloat)time_new.tv_usec-(GLfloat)time_old.tv_usec)/1000000;
    } else {
        time_difference = (GLfloat)0;
    }

    if(time_difference > 0.33f){
        time_difference = 0;
    }

    return time_difference;
}

