#include "stm32f10x.h"
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include "randomness.h"

int RANDOM_RANGE(int min, int max)
{
	return min + rand() % (max - min + 1);
}

int RANDOM_LOOT()
{
	return rand()%2;
}
