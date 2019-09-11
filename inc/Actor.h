#ifndef ACTOR_H_
#define ACTOR_H_

//#include "Compiler.h"
#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
//class Compiler;
class StudentWorld;
class Actor;

//bool canMove(Actor* bug, int x, int y);

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, int team, int depth)
		: GraphObject(imageID, startX, startY, right, depth), m_dead(false), m_world(world), m_team(team)
	{

	}

	~Actor() {}

	StudentWorld* world() const { return m_world; } 

	void dead() { m_dead = true; }
	bool isDead() const { return m_dead; }

	virtual bool canBlock() const { return false; }

	int team() const { return m_team; }
	void setTeam(int team) { m_team = team; }
	
private:
	bool m_dead;
	int m_team;
	StudentWorld* m_world;
};

class Player : public Actor
{
public:
	Player(StudentWorld* world, int imageID, int startX, int startY, int team)
		: Actor(world, imageID, startX, startY, team, 0)
	{

	}

	void move(int x, int y);
	void dropPiece();
private:

};

class Piece : public Actor
{
public:
	Piece(StudentWorld* world, int imageID, int startX, int startY, int team)
		: Actor(world, imageID, startX, startY, team, 1), m_safe(false), m_marked(false)
	{}
	bool isSafe() const { return m_safe; }
	void safe() { m_safe = true; }
	void notSafe() { m_safe = false; }

	bool isMarked() const { return m_marked; }
	void mark() { m_marked = true; }
	void unMark() { m_marked = false; }
private:
	bool m_safe;
	bool m_marked;
};

class Board : public Actor
{
public:
	Board(StudentWorld* world, int imageID, int startX, int startY)
		: Actor(world, imageID, startX, startY, -1, 2)
	{
	}
};




#endif // ACTOR_H_
