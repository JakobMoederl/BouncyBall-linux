#include "good_smiley.h"
#include "game.h"

GoodSmiley::GoodSmiley(void)
{
	type = BALL_GOOD;
}


GoodSmiley::~GoodSmiley(void)
{
}

void GoodSmiley::doKollision(Ball& object){
	if(object.getClass() == BALL_PLAYER){
		death();
		extern Game game;
		game.catchSmiley();
	}
}
/*
void GoodSmiley::doKollision(Block& object){
	
}*/