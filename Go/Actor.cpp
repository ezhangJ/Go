#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include <list>
#include <cmath>
#include <algorithm>
#include <string>


#define PI 3.14159265
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
// remember to check if grahopper doesn't bite itself 
// MAKE BABY MOVE EVERY 3 ticks
// REMEMBER TO MAKE FUNCTION IN ACTOR THAT CHECKS iF ACTOR IS PEBBLE CANT USE IMG ID
// DEFAULT will return false but in pebble class will return true
// MAKE THE InHERITANCE BETTER
// switch to using map
// make sure ant is reseting was blocked correctly


void Player::move(int x, int y)
{
	if (x < VIEW_WIDTH  && y < VIEW_HEIGHT  && x >= 0 && y >= 0)
		moveTo(x, y);
}

void Player::dropPiece()
{

}
