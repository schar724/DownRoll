/*
Authors: Daniel Bahrami, Scott Charles
Instructor: Paul Pospisil

Purpose: Handles Events such
1) Collision with the ball and the platform
2) If the ball is within the gap of the platform
3) Collision with the ball and the border

*/
#include <stdio.h>
#include <osbind.h>
#include <stdlib.h>
#include "include/events.h"


void collision(struct Ball *ball, struct Platform platforms [], struct ScoreBox *scorebox)
{
	if(ball->bottomRightCornerY >= 1 && ball->bottomRightCornerY <= platforms[0].yCord)
	{
		withinGap(ball,platforms[0],scorebox);
	}
	else if(ball->bottomRightCornerY > (platforms[0].yCord) && ball->bottomRightCornerY <= platforms[1].yCord)
	{
		withinGap(ball,platforms[1],scorebox);
	}
	else if(ball->bottomRightCornerY > (platforms[1].yCord) && ball->bottomRightCornerY <= platforms[2].yCord)
	{
		withinGap(ball,platforms[2],scorebox);
	}
	else if(ball->bottomRightCornerY > (platforms[2].yCord) && ball->bottomRightCornerY <= platforms[3].yCord)
	{
		withinGap(ball,platforms[3],scorebox);
	}
	else if(ball->bottomRightCornerY > (platforms[3].yCord) && ball->bottomRightCornerY <= platforms[4].yCord)
	{
		withinGap(ball,platforms[4],scorebox);
	}
	else if(ball->bottomRightCornerY > (platforms[4].yCord) && ball->bottomRightCornerY <= platforms[5].yCord)
	{
		withinGap(ball,platforms[5],scorebox);
	}
	else
	{
		
	}
}
void withinGap(struct Ball *ball, struct Platform pf,struct ScoreBox *scorebox)
{
	if(ball->x > pf.startGap && ball->bottomRightCornerX < pf.endGap)
	{
		ball->hit = 0;
		scorebox->score = scorebox->score + 1;
	}
	else
	{
		platformCollision(ball, pf);
	}
	
}

void platformCollision(struct Ball *ball, struct Platform pf)
{
	if(ball->bottomRightCornerY >= pf.yCord || ball->bottomRightCornerY <= (pf.yCord+12))
	{
		
		ball->hit = 1;
		ball->bottomRightCornerY = pf.yCord;
		ball->y = ball->bottomRightCornerY - 16;
	}
}

void borderCollision(struct Ball *ball)
{
	if(ball->x <= startOfBorder)
	{
		ball->x = (startOfBorder+1);
		ball->bottomRightCornerX = ball->x +16;
	}
	else if(ball->bottomRightCornerX >= endOfBorder)
	{
		ball->bottomRightCornerX = (endOfBorder-1);
		ball->x = ball->bottomRightCornerX - 16;
	}
	else
	{
		/*Nothing*/
	}
}