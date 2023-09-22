/*
TEST
1. Print test value
2. Print message 'Hello World' once a second
*/

#include <unistd.h>
#include <stdio.h>
#include "print.h"

int main()
{
	printf("TEST VALUE = [%d]\n", TEST_VALUE);

	int counter = 0;
	while(1)
	{
		counter++;
		PrintMessage("Hello World!");
		sleep(1);
	}
	return 0;
}
