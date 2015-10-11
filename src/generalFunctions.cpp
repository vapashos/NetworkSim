/*
 * generalFunctions.cpp
 *
 *  Created on: Sep 7, 2015
 *      Author: vapashos
 */

#include <cstdlib>
#include <ctime>
#include <unistd.h>
int getRandomNumber(int max,int min=0){
	sleep(1);
	srand(static_cast <unsigned> (time(NULL)));
	return min + (rand() % (int)(max - min + 1));
}


float getRandomNumber(float max,float min=0){
	sleep(1);
	srand(static_cast <unsigned> (time(NULL)));
	return min + (rand() / (RAND_MAX / max - min ))-0.1;
}
