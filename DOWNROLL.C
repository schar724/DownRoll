/*
Authors: Daniel Bahrami, Scott Charles
Instructor: Paul Pospisil

Purpose: Main Game Module.

*/
#include <stdio.h>
#include <stdlib.h>
#include "include/downroll.h"
#include "include/constants.h"
#include "include/psg.h"
#include "include/music.h"


const UINT8 arrayScreen[32256];



int main()
{
	UINT32 timeThen = 0;
	UINT32 timeNow = 0;
	UINT32 timeElapsed = 0;
	UINT32 music_timer = 0;
	
	UINT16 *FB = get_video_base();
	UINT16 *FB2 = (UINT16 *) getFBAddress();/*Second Frame Buffer*/
	struct Model model;

	setUpGame(&model);
	start_music();
	
	/*main game loop*/
	while(model.ball.bottomRightCornerY > 16 && model.scorebox.score < 100) 
	{
		processAsyncEvents(&(model.ball));
		
		timeNow = get_time();
		timeElapsed = timeNow - timeThen;
		if(timeElapsed > 0)
		{
			processSyncEvents(&model);


			Vsync();
			render(&model,FB);
			set_video_base(FB);
			
			if(update_music(music_timer))
			{
				music_timer = 0;
			}
			else
			{
				music_timer++;
			}
			
			timeThen = timeNow;
	
		}
		
		processAsyncEvents(&(model.ball));
		
		timeNow = get_time();
		timeElapsed = timeNow - timeThen;
		if(timeElapsed > 0)
		{
			processSyncEvents(&model);

			Vsync();
			render(&model,FB2);
			set_video_base(FB2);
			
			if(update_music(music_timer))
			{
				music_timer = 0;
			}
			else
			{
				music_timer++;
			}
				
			timeThen = timeNow;
		}
	}
	
	Vsync();
	set_video_base(FB);
	stop_sound();
	return 0;
}
void processAsyncEvents(struct Ball *ball)
{
	move_ball(ball);
	checkBallBottomCollision(ball);
}
void processSyncEvents(struct Model *model)
{
	movePlatforms(&(model->platforms));
	collision(&(model->ball), &(model->platforms), &(model->scorebox));
}
void setUpGame(struct Model *model)
{

	model->platforms[0] = generate_platform(lowerPf, upperPf, defaultXcordPf, defaultYcordPf, defaultDeltaYPf);
	model->platforms[1] = generate_platform(lowerPf, upperPf, defaultXcordPf, defaultYcordPf + (whiteSpacePf), defaultDeltaYPf);
	model->platforms[2] = generate_platform(lowerPf, upperPf, defaultXcordPf, defaultYcordPf + (whiteSpacePf * 2), defaultDeltaYPf);
	model->platforms[3] = generate_platform(lowerPf, upperPf, defaultXcordPf, defaultYcordPf + (whiteSpacePf * 3), defaultDeltaYPf);
	model->platforms[4] = generate_platform(lowerPf, upperPf, defaultXcordPf, defaultYcordPf + (whiteSpacePf * 4), defaultDeltaYPf);
	model->platforms[5] = generate_platform(lowerPf, upperPf, defaultXcordPf, defaultYcordPf + (whiteSpacePf * 5), defaultDeltaYPf);

	model->screen.startBorder = 0;
	model->screen.endBorder = 639; 
	
	model->ball.x = 344;
	model->ball.y = 125;
	model->ball.deltaX = 15;
	model->ball.deltaY = defaultDeltaYPf; /*Same as platform delta Y*/
	
	model->ball.bottomRightCornerX = model->ball.x + 16;
	model->ball.bottomRightCornerY = model->ball.y + 16;
	
	model->ball.hit = 1;
	model->ball.height = 16;
	model->ball.width = 16;
	
	model->scorebox.score = 0;
	model->scorebox.xCord = 0;
	model->scorebox.yCord = 0;
	model->scorebox.maxScore = 0;
	
}

void checkBallBottomCollision(struct Ball *ball)
{
	if(ball->bottomRightCornerY >= 390)
	{
		ball->bottomRightCornerY = 390;
		ball->y = ball->bottomRightCornerY - 16;
	}
}
UINT32 get_time()
{
	UINT32 timeNow;
	UINT32 *timer;
	long old_ssp;
	timer = (UINT32 *)0x462;
	old_ssp = Super(0);  /* enter privileged mode */
	timeNow = *timer;
	Super(old_ssp); /* exit privileged mode */
	return timeNow;
}

UINT8* getFBAddress()
{
	UINT8* base;
	UINT16 difference;
	base = arrayScreen;
	difference = (int) base;
	difference %= 0x100;
	difference = 0x100 - difference;
	return base + difference;
}