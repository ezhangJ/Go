#include "StudentWorld.h"
#include "Field.h"
#include "Compiler.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::loadField()
{
	Field f;
	string fieldFile = getFieldFilename();
	
	string error;
	if (f.loadField(fieldFile, error) != Field::LoadResult::load_success)
	{
		setError(fieldFile + " " + error);
		return false; // something bad happened!
	}
	

	//get names fo files of ants
	/*
	vector<string> fileNames = getFilenamesOfAntPrograms();

	// Creat new compiler objects
	compilerForEntrant0 = new Compiler;
	compilerForEntrant1 = new Compiler;
	compilerForEntrant2 = new Compiler;
	compilerForEntrant3 = new Compiler;
	*/
	// Compile all the source files to make sure there is no errors
	/*
	switch (fileNames.size())
	{
	case 4:
		if (!compilerForEntrant3->compile(fileNames[3], error))
		{
			setError(fileNames[3] + " " + error);
			return GWSTATUS_LEVEL_ERROR;
		}
	case 3:
		if (!compilerForEntrant2->compile(fileNames[2], error))
		{
			setError(fileNames[2] + " " + error);
			return GWSTATUS_LEVEL_ERROR;
		}
	case 2:
		if (!compilerForEntrant1->compile(fileNames[1], error))
		{
			setError(fileNames[1] + " " + error);
			return GWSTATUS_LEVEL_ERROR;
		}
	case 1:
		if (!compilerForEntrant0->compile(fileNames[0], error))
		{
			setError(fileNames[0] + " " + error);
			return GWSTATUS_LEVEL_ERROR;
		}

	}
	*/
	for (int x = 0; x < VIEW_WIDTH; x++)        // adding stuff to the list from the field
		for (int y = 0; y < VIEW_HEIGHT; y++)
		{
			Field::FieldItem item = f.getContentsOf(x, y); // read the field  ad create new objects based on items on the field
			
			// checking what type it is
			if (item == Field::FieldItem::rock)    
			{
				Actor* ptr = new Actor(this, 8 , x, y);
				m_actorlist[y][x].push_front(ptr);
			}

			if (item == Field::FieldItem::water)
			{
				Actor* ptr = new Actor(this, 8, x, y);
				m_actorlist[y][x].push_front(ptr);
			}
			/*
			if (item == Field::FieldItem::food)
			{
				Actor* ptr = new Food(this, x, y, 6000);
				m_actorlist[y][x].push_front(ptr);
			}

			if (item == Field::FieldItem::poison)
			{
				Actor* ptr = new Poison(this, x, y);
				m_actorlist[y][x].push_front(ptr);
			}

			if (item == Field::FieldItem::poison)
			{
				Actor* ptr = new Poison(this, x, y);
				m_actorlist[y][x].push_front(ptr);
			}

			if (item == Field::FieldItem::grasshopper)
			{
				Actor* ptr = new BabyGrasshopper(this, x, y);
				m_actorlist[y][x].push_front(ptr);
				m_numAntHills++;
			}
			
			if (item == Field::FieldItem::anthill0)
			{
				Actor* ptr = new AntHill(this, x, y, 0, compilerForEntrant0);
				m_actorlist[y][x].push_front(ptr);
				m_numAntHills++;
			}
			
			if (item == Field::FieldItem::anthill1)
			{
				Actor* ptr = new AntHill(this, x, y, 1, compilerForEntrant1);
				m_actorlist[y][x].push_front(ptr);
				m_numAntHills++;
			}
			
			
			if (item == Field::FieldItem::anthill2)
			{
				Actor* ptr = new AntHill(this, x, y, 2, compilerForEntrant2);
				m_actorlist[y][x].push_front(ptr);
				m_numAntHills++;
			}
			
			
			if (item == Field::FieldItem::anthill3)
			{
				Actor* ptr = new AntHill(this, x, y, 3, compilerForEntrant3);
				m_actorlist[y][x].push_front(ptr);
				m_numAntHills++;
			}
			*/
		}
	return GWSTATUS_CONTINUE_GAME;
}

list<Actor*>& StudentWorld::getActors(int x, int y) 
{
	return m_actorlist[y][x];
}

