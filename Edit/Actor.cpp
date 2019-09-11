#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include "Compiler.h"
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
/*
int convertToInteger(string s);

bool Insect::canMove( int x, int y)
{
	if (x > VIEW_WIDTH - 1 || y > VIEW_HEIGHT - 1)
		return false;
	if (x < 0 || y < 0)
		return false;
	if (world()->getActors(x, y).size() != 0
		&& !world()->getActors(x, y).front()->canBlock())
		return true;
	else if (world()->getActors(x, y).size() == 0)
		return true;
	else
		return false;
}

bool Insect::pickUpFood(int food)
{
	list<Actor*>& actors = world()->getActors(getX(), getY());
	for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); p++) // check if there is any food where the grasshopper is standing
	{
		if ((*p)->edible())  // if actor is food
		{
			int foodtoAdd = 0;
			if ((*p)->HP() < food)  // if grasshopper takes more than there is than eat how much there is
				foodtoAdd = (*p)->HP();
			else                      // else just eat selected amount
				foodtoAdd = food;
				
			m_food += foodtoAdd;
			(*p)->minusHP(foodtoAdd);
			return true;
		}
	}
	return false;
}

void Insect::dropFood()
{
	Actor* ptr = new Food(world(), getX(), getY(), m_food);
	world()->getActors(getX(), getY()).push_front(ptr);
	m_food = 0;
}
void Insect::eatFood(int food) 
{
	int HPtoAdd = 0;

	if (m_food - food < 0)
		HPtoAdd = m_food;
	else
		HPtoAdd = food;
	 
	addHP(HPtoAdd);
	m_food -= HPtoAdd;

	int rand = randInt(1, 2);  // 50% chance of being stunned after eating
	if (rand == 2)
		addStun(2);
	
	
}
void Insect::checkForTriggerableActor()
{
	list<Actor*>& actors = world()->getActors(getX(), getY());

	for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
	{
		if ((*p)->triggerable() && (*p)->isPool() && !wet())  // adult grass hopper can't be poisoned
		{
			addStun(2);
			isWet(true);// make sure insect cannot be stunned again
		}
		else if ((*p)->triggerable() && !(*p)->isPool())
			minusHP(150);

	}
}
void Insect::changeDirection()
{
	int rand = randInt(1, 4);
	switch (rand)
	{
	case 1:	setDirection(up); break;
	case 2: setDirection(right); break;
	case 3: setDirection(down); break;
	case 4: setDirection(left); break;
	}
}
void Grasshopper::move(int x, int y) 
{
	if (canMove(x, y))
	{
		moveTo(x, y); // move onscreen 
		isWet(false); // after exiting pool make sure insect can be stunned again
		decreaseDistance();  // decreae distanceToWalk by 1
		addStun(2);
	}
	else
	{
		changeDirection();
		addStun(2);
	}

}

void AdultGrasshopper::move(int x, int y) // move is different for AdultGrasshopper
{
	if (stunnedTicks() == 0)
		bite();
	if (stunnedTicks() == 0)
		jump();
	if (stunnedTicks() == 0)
		Grasshopper::move(x, y);
}

void  AdultGrasshopper::jump()
{
	int rand = randInt(1, 10);  // 1/10 to jump
	if (rand == 10) 
	{
		int randRadius, randDegrees;
		double radians;
		do {
			randRadius = randInt(1, 10);
			randDegrees = randInt(0, 360);
			radians = randDegrees*PI / 180.0;
		} while (!canMove(getX() + randRadius * cos(radians), getY() + randRadius * sin(radians))); // choose a valid spot

			moveTo(getX() + randRadius * cos(radians), getY() + randRadius * sin(radians)); // jump within 10 radius
			addStun(2);
	}
		
}
void  AdultGrasshopper::bite()
{
	int randnum = randInt(1, 3);
	if (randnum == 3)
	{
		list<Actor*>& actors = world()->getActors(getX(), getY());
		int rand = 0;
		list<Actor*>::iterator p = actors.begin();
		bool areEnemies = false;

		for (; p != actors.end(); p++)
		{

			if ((*p)->isGrasshopper()) // check for adult grasshopper
			{
				areEnemies = true;
			}

			if ((*p)->isBug())
			{
				areEnemies = true;
			}
		}

		if (areEnemies)
		{
			do {
				rand = randInt(0, actors.size() - 1);
				p = actors.begin();

				for (int i = 0; i < rand; i++)
					p++;

			} while (*p != this && (*p)->isBug() && p != actors.end()); // so doesn't bite itself
			
			if ((*p)->isGrasshopper() && (*p)->immune())
			{
				int randbite = randInt(0, 1);
				if (randbite == 0)
					minusHP(50);
			}

			(*p)->minusHP(50);
			(*p)->bit(true);
			addStun(2);
		}

	}
}
void Grasshopper::doSomething()
{
	
	minusHP(1);  // decrease hp by 1 every tick

	if (HP() <= 0)
		dead();

	if (stunnedTicks() == 0 && !isDead())
	{
		if (HP() >= 1600 && !immune()) // for babygrasshopper check if hp 1600 or over turns into adult grasshopper
		{
			dead();
			Actor* ptr = new AdultGrasshopper(world(), getX(), getY());
			world()->getActors(getX(), getY()).push_front(ptr);
		}
		if (!isDead())
		{
			if (pickUpFood(200))
				eatFood(200);

			if (!immune())
				checkForTriggerableActor();

			if (HP() <= 0)
				dead();

			if (stunnedTicks() == 0 && !isDead())
			{
				if (m_distanceToWalk != 0)
				{
					switch (getDirection())
					{
					case up:  // remember to check if list is empty or not
						move(getX(), getY() + 1);
						break;
					case right:
						move(getX() + 1, getY());
						break;
					case down:
						move(getX(), getY() - 1);
						break;
					case left:
						move(getX() - 1, getY());
						break;
					}
				}
				else
				{
					changeDirection();
					addStun(2);
				}
			}
			else
				decrementStun();
		}
	}
	else
		decrementStun();
}

void Grasshopper::changeDirection()
{
	// set direction to a random direction
	Insect::changeDirection();

	// set distance to walk between 2 and 10 inclusive
	int rand = randInt(2, 10);
	m_distanceToWalk = rand;
}

void AntHill::doSomething()
{
	minusHP(1);  // decrease hp by 1 every tick

	if (HP() <= 0)
		dead();

	if (HP() >= 2000)
		giveBirth();
	//eat food
	pickUpFood(10000);
	eatFood(10000);
	
}

void AntHill::giveBirth()
{
	Actor* ptr = nullptr;
	m_numAnts++;
	switch (team())
	{
	case 0:
		ptr = new Ant(world(), IID_ANT_TYPE0, getX(), getY(), 0, m_antCompiler);
		world()->getActors(getX(), getY()).push_front(ptr);
		break;
	case 1:
		ptr = new Ant(world(), IID_ANT_TYPE1, getX(), getY(), 1, m_antCompiler);
		world()->getActors(getX(), getY()).push_front(ptr);
		break;
	case 2:
		ptr = new Ant(world(), IID_ANT_TYPE2, getX(), getY(), 2, m_antCompiler);
		world()->getActors(getX(), getY()).push_front(ptr);
		break;
	case 3:
		ptr = new Ant(world(), IID_ANT_TYPE3, getX(), getY(), 3, m_antCompiler);
		world()->getActors(getX(), getY()).push_front(ptr);
		break;
	}

	//minus health
	minusHP(1500);
}

void Ant::move(int x, int y)
{
	if (canMove(x, y))
	{
		moveTo(x, y);  
		isWet(false); // after exiting pool make sure insect can be stunned again
		m_wasBlocked = false;
		bit(false);
	}
	else
	{
		m_wasBlocked = true;
	}
}

void Ant::doSomething()
{
	minusHP(1);  // decrease hp by 1 every tick
	
	if (HP() <= 0)
		dead();

	if (!isDead())
		checkForTriggerableActor();

	if (stunnedTicks() == 0 && !isDead())
	{
		interpreter();
	}
	else
		decrementStun();
}


bool Ant::interpreter()
{
	
	bool changedState = false;
	Compiler::Command cmd;
	int commands = 0;

	while(!changedState && commands != 10) // keep running forever for now
	{
		 
		// get the command from element ic of the vector
		if (!m_antCompiler->getCommand(m_ic, cmd))
		{
			dead();
			return false;// error - no such instruction!
		}
			 

		switch (cmd.opcode)
		{
		
		case Compiler::Opcode::moveForward:
			// cause the ant to move forward by
			// updating its x,y coordinates
			moveTheAntForward();
			changedState = true;
			m_ic++; // advance to next instruction
			break;
		case Compiler::Opcode::generateRandomNumber:
			generateRandomNumberUpTo(cmd.operand1);
			m_ic++; // advance to next instruction
			break;
		
		case Compiler::Opcode::if_command:
			// if the condition of the if command is
			// is true, then go to the target position
			// in the vector; otherwise fall through to
			// the next position
			if (conditionTriggered(cmd))
			{
				m_ic = convertToInteger(cmd.operand2);
			}
			else
				m_ic++; // just advance to the next line
			break;
		case Compiler::Opcode::goto_command:
			// just set ic the specified position
			// in operand1
			m_ic = convertToInteger(cmd.operand1);
			break;
		case Compiler::Opcode::faceRandomDirection:
			changeDirection();
			changedState = true;
			m_ic++;
			break;
		case Compiler::Opcode::rotateClockwise:
			switch (getDirection())
			{
			case up: setDirection(right); break;
			case right: setDirection(down); break;
			case down: setDirection(left); break;
			case left: setDirection(up); break;
			}
			changedState = true;
			m_ic++;
			break;
		case Compiler::Opcode::rotateCounterClockwise:
			
			switch (getDirection())
			{
			case up: setDirection(left); break;
			case right: setDirection(up);  break;
			case down: setDirection(right); break;
			case left: setDirection(down); break;
			}
			changedState = true;
			m_ic++;
			break;
		case Compiler::Opcode::pickupFood:
			if (food() + 400 < 1800)
			{
				pickUpFood(400);
			}
			else
				pickUpFood(1800 - food());
			changedState = true;
			m_ic++;
			break;
		case Compiler::Opcode::dropFood:
			dropFood();
			changedState = true;
			m_ic++;
			break;
		case Compiler::Opcode::eatFood:
			eatFood(100);
			changedState = true;
			m_ic++;
			break;
		case Compiler::Opcode::bite:
			bite();
			changedState = true;
			m_ic++;
			break;
		case Compiler::Opcode::emitPheromone:
			emitPheromone();
			changedState = true;
			m_ic++;
			break;
		case Compiler::Opcode::invalid:
			m_ic++;
			break;
			
		}
		commands++;
	}
	
	return true;
}



void Ant::moveTheAntForward()
{
	switch (getDirection())
	{
	case up:  // remember to check if list is empty or not
		move(getX(), getY() + 1);
		break;
	case right:
		move(getX() + 1, getY());
		break;
	case down:
		move(getX(), getY() - 1);
		break;
	case left:
		move(getX() - 1, getY());
		break;
	}
	
}

int convertToInteger(string s)
{
	int total = 0;
	int part = 0;
	for (int i = 0; i < s.size(); i++)
	{
		part = (s[i] - 48) * pow(10, s.size() - 1 - i);
		total += part;
	}
	
	return total;
}

void Ant::generateRandomNumberUpTo(string limit)
{
	char limitChar = limit[0];
	int limitInt = limitChar - 48;
	m_randomInt = randInt(0, limitInt);

}

bool Ant::conditionTriggered(Compiler::Command cmd) const
{
	char operand = cmd.operand1[0];

	switch (operand)
	{
	case '0':
		return isDanger();
		break;
	case '1':
		return pheromoneNear();
		break;
	case '2':
		return wasBit(); // FINISH
		break;
	case '3':
		if (food() != 0)
		{ 
			return true;
		}
		else
			return false;
		break;
	case '4':
		if (HP() <= 25)
			return true;
		else
			return false;
		break;
	case '5':
		return onAntHill();
		break;
	case '6':
		return onFood();
		break;
	case '7':
		return withDanger();
		break;
	case '8':
		return m_wasBlocked; // FINISH
		break;
	case '9':
		return m_randomInt == 0;
		break;
	default:
		return false;
	}
	
}

bool Ant::isDanger() const
{
	int x, y;
	switch (getDirection())
	{
	case up:
		x = getX();
		y = getY() + 1;
		break;
	case right:
		x = getX() + 1;
		y = getY();
		break;
	case down:
		x = getX();
		y = getY() - 1;
		break;
	case left:
		x = getX() - 1;
		y = getY();
		break;
	}

	list<Actor*>& actors = world()->getActors(x, y);

	for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
	{

		if ((*p)->isGrasshopper()) // check for adult grasshopper
		{
			return true;
		}

		if ((*p)->triggerable())
		{
			return true;
		}

		if ((*p)->team() != team() && (*p)->isBug())
		{
			return true;
		}
	}
	return false;
}

bool Ant::onAntHill() const
{
	list<Actor*>& actors = world()->getActors(getX(), getY());

	for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
	{
		if ((*p)->isHill() && (*p)->team() == team())
			return true;
	}
	return false;
}

bool Ant::onFood() const
{

	list<Actor*>& actors = world()->getActors(getX(), getY());

	for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
	{
		if ((*p)->edible())
		{
			return true;
		}
	}
	return false;
}

bool Ant::withDanger() const
{
	list<Actor*>& actors = world()->getActors(getX(), getY());

	for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
	{

		if ((*p)->isGrasshopper()) // check for adult grasshopper
		{
			return true;
		}

		if ((*p)->team() != team() && (*p)->isBug())
		{
			return true;
		}
	}
	return false;
}

void Ant::bite()
{
	list<Actor*>& actors = world()->getActors(getX(), getY());
	int rand = 0;
	list<Actor*>::iterator p = actors.begin();
	bool areEnemies = false;

	for (; p != actors.end(); p++)
	{

		if ((*p)->isGrasshopper()) // check for adult grasshopper
		{
			areEnemies = true;
		}

		if ((*p)->team() != team() && (*p)->isBug())
		{
			areEnemies = true;
		}
	}

	if (areEnemies)
	{
		do {
			rand = randInt(0, actors.size() - 1);
			p = actors.begin();

			for (int i = 0; i < rand; i++)
				p++;

		} while (*p != this && (*p)->team() != team() && (*p)->isBug() && p != actors.end()); // so doesn't bite itself
		if ((*p)->isGrasshopper() && (*p)->immune())
		{
			int randbite = randInt(0, 1);
			if (randbite == 0)
				minusHP(50);
		}
				(*p)->minusHP(15);
				(*p)->bit(true);
			
	}
}

bool Ant::pheromoneNear() const
{
	int x, y;
	switch (getDirection())
	{
	case up:
		x = getX();
		y = getY() + 1;
		break;
	case right:
		x = getX() + 1;
		y = getY();
		break;
	case down:
		x = getX();
		y = getY() - 1;
		break;
	case left:
		x = getX() - 1;
		y = getY();
		break;
	}

	list<Actor*>& actors = world()->getActors(x, y);

	for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); p++)
	{

		if ((*p)->isPheromone() && (*p)->team() == team()) // check for adult grasshopper
		{
			return true;
		}

	}
	return false;
}
void Ant::emitPheromone() const
{
	Actor* ptr = nullptr;
	bool isPheromone = false;

	list<Actor*>& actors = world()->getActors(getX(), getY());
	list<Actor*>::iterator p = actors.begin();
	for (; p != actors.end(); p++)
	{
		if ((*p)->isPheromone() && (*p)->team() == team())
		{
			isPheromone = true;
			break;
		}
	}
	
	if (!isPheromone)
	{
		switch (team())
		{
		case 0:
			ptr = new Pheromone(world(), IID_PHEROMONE_TYPE0, getX(), getY(), 0);
			world()->getActors(getX(), getY()).push_front(ptr);
			break;
		case 1:
			ptr = new Pheromone(world(), IID_PHEROMONE_TYPE1, getX(), getY(), 1);
			world()->getActors(getX(), getY()).push_front(ptr);
			break;
		case 2:
			ptr = new Pheromone(world(), IID_PHEROMONE_TYPE2, getX(), getY(), 2);
			world()->getActors(getX(), getY()).push_front(ptr);
			break;
		case 3:
			ptr = new Pheromone(world(), IID_PHEROMONE_TYPE3, getX(), getY(), 3);
			world()->getActors(getX(), getY()).push_front(ptr);
			break;
		}
	} 
	else
	{
		(*p)->addHP(256);
		if ((*p)->HP() > 768)
			(*p)->setHP(768);
	}
}
void Pheromone::doSomething()
{
	minusHP(1);

}
*/