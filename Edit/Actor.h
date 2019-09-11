#ifndef ACTOR_H_
#define ACTOR_H_

//#include "Compiler.h"
#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
//class Compiler;
//class StudentWorld;
class Actor;

//bool canMove(Actor* bug, int x, int y);

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY)
		: GraphObject(imageID, startX, startY, right, 1), m_dead(false), m_world(world), m_team(1)
	{

	}

	~Actor() {}

	StudentWorld* world() const { return m_world; } 

	void dead() { m_dead = true; }
	bool isDead() const { return m_dead; }


	int team() const { return m_team; }
	void setTeam(int team) { m_team = team; }
	
private:
	bool m_dead;
	int m_team;
	StudentWorld* m_world;
};

/*
class Insect : public Actor
{

public:
	Insect(StudentWorld* world, int startX, int startY, int imageID, int depth)
		: Actor(world, imageID, startX, startY, depth), m_stunnedTicks(0), m_wet(false), m_food(0)
	{}

	int stunnedTicks() { return m_stunnedTicks; }
	void addStun(int ticks) { m_stunnedTicks += ticks; }
	void decrementStun() { m_stunnedTicks--; }

	virtual bool hasHealth() const { return true; }
	virtual bool immune() const { return false; }
	virtual bool isBug() const { return true; }
	
	bool canMove( int x, int y);
	virtual void move(int x, int y) = 0;

	bool wet() { return m_wet; }
	void isWet(bool set) { m_wet = set; }
	
	void checkForTriggerableActor();

	void eatFood(int food);
	bool pickUpFood(int food);
	void dropFood();
	int food() const { return m_food; }

	virtual void changeDirection();

private:
	int m_stunnedTicks;
	int m_food;
	bool m_wet;

};


class Ant : public Insect
{
public:
	Ant(StudentWorld* world, int imageID, int startX, int startY, int colonyNum, Compiler* antCompiler)
		: Insect(world, startX, startY, imageID, 1),  m_randomInt(0), m_antCompiler(antCompiler),
		m_ic(0), m_wasBlocked(false), m_wasBit(false)
	{
		setHP(1500);
		changeDirection();
		setTeam(colonyNum);
	}

	virtual bool isAnt() const { return true; }

	virtual void doSomething();
	virtual void move(int x, int y);
	void bite();
	void emitPheromone() const;
	bool interpreter();
	void moveTheAntForward();
	void generateRandomNumberUpTo(std::string limit);
	bool conditionTriggered(Compiler::Command cmd) const;
	bool isDanger() const;
	bool onAntHill() const;
	bool onFood() const;
	bool withDanger() const;
	bool pheromoneNear() const;

private:
	int m_ic;
	int m_randomInt;
	bool m_wasBlocked;
	bool m_wasBit;
	Compiler* m_antCompiler;
};

class AntHill : public Insect 
{
public:
		AntHill(StudentWorld* world, int startX, int startY, int colonyNum, Compiler* antCompiler)
			: Insect(world, startX, startY, IID_ANT_HILL, 2), m_antCompiler(antCompiler), m_numAnts(0)

		{
			setHP(8999);
			setTeam(colonyNum);
		}

		virtual void move(int x, int y) {}

		virtual bool hasHealth() const { return true; }
		virtual bool immune() const { return true; } // NEED TO MAKE IMMUNE RESIST BITES SOMEHOW
		virtual bool isHill() const { return true; }
		virtual bool isBug() const { return false; }

		virtual void doSomething();
		void giveBirth();
		
private:
	Compiler* m_antCompiler;
	int m_numAnts;
	
};

class Grasshopper : public Insect
{
public:
	Grasshopper(StudentWorld* world, int startX, int startY, int imageID)
		: Insect(world, startX, startY, imageID, 1), m_distanceToWalk(0)
	{
		changeDirection();
	}

	virtual bool isGrasshopper() const { return true; }

	virtual void doSomething();
	virtual void move(int x, int y);

	void decreaseDistance() { m_distanceToWalk--; }
	virtual void changeDirection();
	
	

private:
	int m_distanceToWalk;
};

class BabyGrasshopper : public Grasshopper //Actor
{
public:
	BabyGrasshopper(StudentWorld* world, int startX, int startY)// int imageID = IID_BABY_GRASSHOPPER)
		: Grasshopper(world, startX, startY, IID_BABY_GRASSHOPPER) //(world, imageID, startX, startY, 1)
	{
		setHP(500);
	}
};

class AdultGrasshopper : public Grasshopper
{
public:
	AdultGrasshopper(StudentWorld* world, int startX, int startY)
		: Grasshopper(world, startX, startY, IID_ADULT_GRASSHOPPER)
	{
		setHP(1600);
	}

	virtual bool immune() const { return true; }
	virtual void move(int x, int y);

	void jump();
	void bite();

};




// STUFF THAT DOESN'T MOVE
class Pebble : public Actor
{
public:
	Pebble(StudentWorld* world, int startX, int startY)
		: Actor(world, IID_ROCK, startX, startY, 1)
	{}
	virtual void doSomething() {}
	virtual bool canBlock() const { return true; }

};

class Triggerable : public Actor
{
public:
	Triggerable(StudentWorld* world, int imageID, int startX, int startY)
		: Actor(world, imageID, startX, startY, 2)
	{}
	virtual bool triggerable() const { return true; }
};

class WaterPool : public Triggerable
{
public:
	WaterPool(StudentWorld* world, int startX, int startY)
		: Triggerable(world, IID_WATER_POOL, startX, startY)
	{}
	
	virtual bool isPool() const { return true; }
	virtual void doSomething() {}

};

class Poison : public Triggerable
{
public:
	Poison(StudentWorld* world, int startX, int startY)
		: Triggerable(world, IID_POISON, startX, startY)
	{}
	virtual void doSomething() {}
};

class Food : public Actor
{
public:
	Food(StudentWorld* world, int startX, int startY, int food)  // ask about why making the constant of food 6000 it wont work
		: Actor(world, IID_FOOD, startX, startY, 2)
	{
		setHP(food);
	}
	virtual void doSomething() {};
	virtual bool hasHealth() const { return true; }
	virtual bool edible() const { return true; }
	

};



class Pheromone : public Actor
{
public:
	Pheromone(StudentWorld* world, int imageID, int startX, int startY, int team)
		: Actor(world, imageID, startX, startY, 2)
	{
		setHP(256);
		setTeam(team);
	}
	virtual bool hasHealth() const { return false; }
	virtual bool isPheromone() const { return true; }
	virtual void doSomething();
	
};
*/
#endif // ACTOR_H_
