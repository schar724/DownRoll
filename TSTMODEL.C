/*
Authors: Daniel Bahrami, Scott Charles
Instructor: Paul Pospisil

Purpose: Tests Functions and Structs in Model.c

*/
#include <stdio.h>
#include <osbind.h>
#include <stdlib.h>
#include "model.h"
void tst_NotHit_ball(struct Ball *ball, char kbInput);
void hitOrNot(struct Ball *ball);
void keyPressed(struct Ball *ball);
void test_platform_array(struct Platform platforms[]);
/*Set cords for testing*/
#define STARTYCORD 200
#define STARTXCORD 320
int main()
{	
	struct Ball *testBall;
	struct Platform platforms[6];
	
	struct Platform *plat0;
	struct Platform *plat1;
	struct Platform *plat2;
	struct Platform *plat3;
	struct Platform *plat4;
	struct Platform *plat5;
	
	int lower = 1, upper = 6;
	int defaultYcord = 400;
	int defaultXcord = 214;
	int defaultDeltaY = 5;
	int whiteSpace = 42;
	
	plat0 = (struct Platform*) malloc(sizeof(struct Platform));
	plat1 = (struct Platform*) malloc(sizeof(struct Platform));
	plat2 = (struct Platform*) malloc(sizeof(struct Platform));
	plat3 = (struct Platform*) malloc(sizeof(struct Platform));
	plat4 = (struct Platform*) malloc(sizeof(struct Platform));
	plat5 = (struct Platform*) malloc(sizeof(struct Platform));
	
	testBall = (struct Ball*) malloc(sizeof(struct Ball));
	testBall->x = STARTXCORD;
	testBall->y = STARTYCORD;
	testBall->deltaX = 1;
	testBall->hit = 0;
	testBall->height = 1;
	testBall->width = 1;

	/*Run twice to get both keys tested*/
	printf("Press a key: ");
	move_ball(testBall);
	keyPressed(testBall);
	
	/*Ball not hit*/
	hitOrNot(testBall);
	/*Ball was hit*/
	testBall->y = STARTYCORD;
	testBall->hit = 1;
	move_ball(testBall);
	hitOrNot(testBall);
	
	free(testBall);
	Cconin();
	
	plat0->platformType = (rand() % (upper - lower + 1)) + lower;
	plat0->xCord = defaultXcord;
	plat0->yCord = defaultYcord;
	plat0->deltaY = defaultDeltaY;
	
	plat1->platformType = (rand() % (upper - lower + 1)) + lower;
	plat1->xCord = defaultXcord;
	plat1->yCord = defaultYcord + (whiteSpace);
	plat1->deltaY = defaultDeltaY;
	
	plat2->platformType = (rand() % (upper - lower + 1)) + lower;
	plat2->xCord = defaultXcord;
	plat2->yCord = defaultYcord + (whiteSpace * 2);
	plat2->deltaY = defaultDeltaY;
	
	plat3->platformType = (rand() % (upper - lower + 1)) + lower;
	plat3->xCord = defaultXcord;
	plat3->yCord = defaultYcord + (whiteSpace * 3);
	plat3->deltaY = defaultDeltaY;
	
	plat4->platformType = (rand() % (upper - lower + 1)) + lower;
	plat4->xCord = defaultXcord;
	plat4->yCord = defaultYcord + (whiteSpace * 4);
	plat4->deltaY = defaultDeltaY;
	
	plat5->platformType = (rand() % (upper - lower + 1)) + lower;
	plat5->xCord = defaultXcord;
	plat5->yCord = defaultYcord + (whiteSpace * 5);
	plat5->deltaY = defaultDeltaY; 
	
	platforms[0] = *plat0;
	platforms[1] = *plat1;
	platforms[2] = *plat2;
	platforms[3] = *plat3;
	platforms[4] = *plat4;
	platforms[5] = *plat5;
	
	
	
	test_platform_array(platforms);
	Cconin();
	
    return 0;
}

void hitOrNot(struct Ball *ball)
{
	if(ball->y < STARTYCORD)
	{
		printf("Ball was not hit!\n");
	}
	else if(ball->y == ball->y)
	{
		printf("Ball was hit!\n");
	}
	else
	{
		printf("Should not be down here: %i\n", ball->y);
	}
}

void keyPressed(struct Ball *ball)
{
	if(ball->x == STARTXCORD-ball->deltaX)
	{
		printf("You pressed Left!\n");
	}
	else if(ball->x == STARTXCORD+ball->deltaX)
	{
		printf("You pressed Right!\n");
	}
	else
	{
		printf("Should not be down here: %i\n", ball->x);
	}
}

void test_platform_array(struct Platform platforms[]){
	
	int i;
	int type;
	struct Platform temp;
	int y;
	for (i = 0; i < 6; i++)
	{
		temp = platforms[i];
		type = temp.platformType;
		y = temp.yCord;
		printf("Type: %i  YCord: %i\n",type, y);
	}
	
}
