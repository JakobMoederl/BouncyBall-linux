#ifndef _GAME_H_
#define _GAME_H_

#include "level.h"
#include "../ball/player.h"

class Game
{
public:
	//standerkonstruktor (kein anderer Verf�gbar)
	Game(void);
	//destruktor
	~Game(void);
	
	bool initFirst();
	bool init(int lvlNumber, Level& lvl);
	void playFrame(GLfloat time_difference);
	void calcCollisions();
	void doMovement();
	void doAnimations();
	void finished(void);
	void loose(void);
	void win(void);
	bool isWon();
	void resetLvl();
	void catchSmiley(void);

	void draw();
	void drawInterface();
	void drawBackground();
	void drawNextLvl();
	void drawNextLvlBackground();
	void drawDarkScreen(GLfloat);
	void drawEndOfGame();

	Player& getPlayer();
	int getActualLvl();
	int getActiveLvl();
	Level& getLvl();
	Level& getLvl(int activeLvl);

	void moveLeft(void);
	void moveRight(void);
	void moveStop(void);
	void moveJump(GLfloat);
	void setWantJump(bool jump);
	bool isMoving(void);
	bool isMovingLeft(void);
	bool isMovingRight(void);
	bool wantJump(void);

	void setFrameWidth(int frameWidth);
	void setFrameHeight(int frameHeight);
	void setFrameDimension(int width, int height);

	void setPause(bool pause);
	bool isPause(void);

	void setDone(bool done);
	bool isDone();

	void setFont(GLuint font);
	GLuint getFont();
	void print(const char *fmt, GLfloat x, GLfloat y, ...);

	void setJumpSpeed(GLfloat);
	GLfloat getJumpSpeed(void);

private:
	//lvlOject which contains all blocks and smileys of the current level
	Level* lvl;
	//number of the current level
	int lvlNumber;
	int activeLvl;
	int lvlAnz;

	// Fullscreen Flag Set To Fullscreen Mode By Default	
	bool fullscreen;	
	//frame width in pixel
	int frame_width;
	//frame height in pixel
	int frame_height;

	//flag if player wants to accelerate in the left direction
	bool move_left;
	//flag if player wants to accelerate in the right direction
	bool move_right;
	//flag if player wants to jump
	bool jump;

	GLfloat jump_speed;
	//acceleration of the player (when player wants to accelerate), in units/s²
	GLfloat acceleration;
	//acceleration of the player (when ball rolls on the floor)
	GLfloat acceleration_ground;
	//acceleration of the player (when ball is not on the floor)
	GLfloat acceleration_air;

	GLfloat gravity;

	//Font object
	GLuint  font;

	//the time since the last calculations cycle
	GLfloat time_difference;
	//common timer
	GLfloat counter;
    //time total of all levels
	GLfloat total_time;
	//death counter
	int deaths;

	//x position when lvl was won
	GLfloat x_lvl_won;
	GLfloat y_lvl_won;

	//pause flag
	bool pause;
	//finished flag
	bool done;
	//lost the lvl
	bool lost;
	//won the lvl
	bool won;
	// set true when last lvl is won
	bool last_won;

	int frames;
	int frames_last;
	float frames_displayed_last;
};

#endif