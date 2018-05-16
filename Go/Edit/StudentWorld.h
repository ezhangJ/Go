#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Compiler.h"

#include <string>
#include <list>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir), m_ticks(0)//, m_numAntHills(0)
	{
		//compilerForEntrant0 = nullptr;
		//compilerForEntrant1 = nullptr;
		//compilerForEntrant2 = nullptr;
		//compilerForEntrant3 = nullptr;

	}

	~StudentWorld()
	{
		cleanUp(); 
		//delete compilerForEntrant0;
		//delete compilerForEntrant1;
		//delete compilerForEntrant2;
		//delete compilerForEntrant3;
	}

	virtual int init()
	{
		return loadField();
	}

	virtual int move()
	{
		m_ticks++; // update ticks
		if (m_ticks >= 2000)
		{
			return GWSTATUS_NO_WINNER;
		}
		/*
		int numAnt[4] = { 0, 0, 0, 0 };
		std::string winners[4];
		
		for (int x = 0; x < VIEW_WIDTH; x++)
			for (int y = 0; y < VIEW_HEIGHT; y++)
			{
				for (std::list<Actor*>::iterator p = m_actorlist[y][x].begin(); p != m_actorlist[y][x].end();p++)
				{
					if ((*p)->isAnt())
					{
						switch ((*p)->team())
						{
						case 0: numAnt[0]++; break;
						case 1: numAnt[1]++; break;
						case 2: numAnt[2]++; break;
						case 3: numAnt[3]++; break;
						}
					}
				}
			}

		int largestNumAnt = numAnt[0];
		int largestIndex = 0;
		for (int i = 0; i < 4; i++)
		{
			if (largestNumAnt < numAnt[i])
			{
				largestNumAnt = numAnt[i];
				largestIndex = i;
			}
		}

		bool tie = false;
		for (int i = 0; i < 4; i++)
		{
			if (largestIndex != i && (numAnt[largestIndex] == numAnt[i]))
				tie = true;
		}

		switch (largestIndex)
		{
		case 0:
			winners[0] = "*";
			break;
		case 1:
			winners[1] = "*";
			break;
		case 2:
			winners[2] = "*";
			break;
		case 3:
			winners[3] = "*";
			break;
		}
		
		if (m_ticks >= 2000)
		{

			if (numAnt[largestIndex] != 0 && !tie)
			{
				switch (largestIndex)
				{
				case 0:
					setWinner(compilerForEntrant0->getColonyName());
					return GWSTATUS_PLAYER_WON;
					break;
				case 1:
					setWinner(compilerForEntrant1->getColonyName());
					return GWSTATUS_PLAYER_WON;
					break;
				case 2:
					setWinner(compilerForEntrant2->getColonyName());
					return GWSTATUS_PLAYER_WON;
					break;
				case 3:
					setWinner(compilerForEntrant3->getColonyName());
					return GWSTATUS_PLAYER_WON;
					break;
				}
			}
			return GWSTATUS_NO_WINNER;
		}
			
		// update Status Line
		std::ostringstream oss;
		oss << std::setw(5) << m_ticks;
	
		std::ostringstream oss0;
		oss0.fill('0');
		oss0 << std::setw(2) << numAnt[0];
		std::ostringstream oss1;
		oss1.fill('0');
		oss1 << std::setw(2) << numAnt[1];
		std::ostringstream oss2;
		oss2.fill('0');
		oss2 << std::setw(2) << numAnt[2];
		std::ostringstream oss3;
		oss3.fill('0');
		oss3 << std::setw(2) << numAnt[3];
		
		std::string s = "Ticks:" + oss.str() + " - " + compilerForEntrant0->getColonyName()+ winners[0] + ": " + oss0.str() + "  "
			+ compilerForEntrant1->getColonyName() + winners[1] + ": " + oss1.str() + "  " + compilerForEntrant2->getColonyName() + winners[2] + ": " + oss2.str() + "  "
			+ compilerForEntrant3->getColonyName() + winners[3] + ": " + oss3.str();
		
		

		setGameStatText(s);

		
		//make everything doSomethng()
		for (int x = 0; x < VIEW_WIDTH; x++)        
			for (int y = 0; y < VIEW_HEIGHT; y++)
			{
				for (std::list<Actor*>::iterator p = m_actorlist[y][x].begin(); p != m_actorlist[y][x].end();)
				{

					if (!(*p)->didSomething())  // make sure you don't tell element to do something twice
					{
						(*p)->doSomething();
						(*p)->doneSomething(true);

						if ((*p)->hasHealth() && (y != (*p)->getY() || x != (*p)->getX())) // change position in data structure
						{
							m_actorlist[(*p)->getY()][(*p)->getX()].push_front(*p);
							p = m_actorlist[y][x].erase(p);
						}
						else
							p++;
					}
					else
						p++;
				}
			}
		
		 // everything did something
		for (int x = 0; x < VIEW_WIDTH; x++)       
			for (int y = 0; y < VIEW_HEIGHT; y++)
			{
				for (std::list<Actor*>::iterator p = m_actorlist[y][x].begin(); p != m_actorlist[y][x].end();p++)
				{
					(*p)->doneSomething(false);
				}
			}
			
		// Get rid of dead stuff
		for (int x = 0; x < VIEW_WIDTH; x++)        // adding stuff to the list from the field
			for (int y = 0; y < VIEW_HEIGHT; y++)
			{
				for (std::list<Actor*>::iterator p = m_actorlist[y][x].begin(); p != m_actorlist[y][x].end(); )
				{
					if ((*p)->hasHealth() && ((*p)->isDead() || (*p)->HP() <= 0))
					{
						if (!(*p)->edible() && !(*p)->isPheromone())
						{
							Actor* ptr = new Food(this, x, y, 100); // when insect dies it will drop 100 food
							m_actorlist[y][x].push_front(ptr);
						}

						delete *p;
						p = m_actorlist[y][x].erase(p);
					}
					else
						p++;
				}
			}
			
	*/

		return GWSTATUS_CONTINUE_GAME;
		
	}


	virtual void cleanUp()
	{
		for (int x = 0; x < VIEW_WIDTH; x++)        
			for (int y = 0; y < VIEW_HEIGHT; y++)
			{
				while (m_actorlist[y][x].size() != 0)
				{
					delete m_actorlist[y][x].front();
					m_actorlist[y][x].pop_front();
				}
			}
	}


	int loadField();
	std::list<Actor*>& getActors(int x, int y); // returns reference to list

private:
	std::list<Actor*> m_actorlist[VIEW_HEIGHT][VIEW_WIDTH];
	//int m_numAntHills;
	int m_ticks;
	//Compiler* compilerForEntrant0;
	//Compiler* compilerForEntrant1;
	//Compiler* compilerForEntrant2;
	//Compiler* compilerForEntrant3;
};

#endif // STUDENTWORLD_H_
