#include <stdio.h>
#include <osbind.h>
#include "inlcude/input.h"

char readInput()
{
	char ch = 0;
	if(Cconis())
	{
		ch = (char) Cnecin();
	}
	return ch;
}
