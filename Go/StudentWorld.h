#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <iostream>

#include <string>
#include <list>
#include <vector>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir), m_whiteScore(0), m_blackScore(0)
	{
		m_gameStatus = "Black's Turn";

		for (int x = 0; x < VIEW_WIDTH; x++)
			for (int y = 0; y < VIEW_HEIGHT; y++)
			{
				m_actorlist[y][x] = nullptr;
				m_pieceposition[y][x] = nullptr;
			}
				
	}

	~StudentWorld()
	{
		//cleanUp(); 
	
	}

	virtual int init()
	{
		return loadField();
	}

	virtual int move()
	{
		/*
		m_ticks++; // update ticks
		if (m_ticks >= 2000)
		{
			return GWSTATUS_NO_WINNER;
		}
		*/
		// update Status Line
		/*
		std::ostringstream oss;
		oss << std::setw(5) << m_ticks;
	
		std::ostringstream oss0;
		oss0.fill('0');
		oss0 << std::setw(2);
		std::ostringstream oss1;
		oss1.fill('0');
		oss1 << std::setw(2);
		std::ostringstream oss2;
		oss2.fill('0');
		oss2 << std::setw(2);
		std::ostringstream oss3;
		oss3.fill('0');
		oss3 << std::setw(2);
		*/
		std::ostringstream oss;
		oss << m_blackScore;
		std::ostringstream oss1;
		oss1 << m_whiteScore;

		std::string status = m_gameStatus;
		std::string score = "Black Score: " + oss.str() + "   " + "White Score: " + oss1.str(); //"Ticks:" + oss.str() + " - "  + oss0.str() + "  " + ": " + oss1.str() +  ": " + oss2.str() + "  " +  ": " + oss3.str();
		
		setGameStatText(status);
		setGameScoreText(score);

		// Move players around
		int value = 0;
		
		getKey(value);
		switch (value) {
			case KEY_PRESS_TAB:
				if (m_whiteScore > m_blackScore)
				{
					setWinner("White");
					return GWSTATUS_PLAYER_WON;
				}
				else if (m_blackScore > m_whiteScore)
				{
					setWinner("Black");
					return GWSTATUS_PLAYER_WON;
				}
				return GWSTATUS_NO_WINNER;
				break;
			case KEY_PRESS_UP:
				m_player->move(m_player->getX(), m_player->getY() + 1);
				break;
			case KEY_PRESS_DOWN:
				m_player->move(m_player->getX(), m_player->getY() - 1);
				break;
			case KEY_PRESS_LEFT:
				m_player->move(m_player->getX() - 1, m_player->getY());
				break;
			case KEY_PRESS_RIGHT:
				m_player->move(m_player->getX() + 1, m_player->getY());
				break;
			case KEY_PRESS_DROP:
				
				int x = m_player->getX();
				int y = m_player->getY();
				int team = m_player->team();
				if (m_pieceposition[y][x] == nullptr)
				{
					if (team == 0) {
						Piece* ptr = new Piece(this, IID_WHITEPLAYER, x, y, 0);
						m_pieceposition[y][x] = ptr;
						m_pieces.push_back(ptr);
						m_whiteScore++;
					}
					else if (team == 1) {
						Piece* ptr = new Piece(this, IID_BLACKPLAYER, x, y, 1);
						m_pieceposition[y][x] = ptr;
						m_pieces.push_back(ptr);
						m_blackScore++;
					}

					delete m_player;
					if (team == 0)
					{
						m_player = new Player(this, IID_BLACKPLAYER, x, y, 1);
						m_gameStatus = "Black's Turn";
					}
					else if (team == 1)
					{
						m_player = new Player(this, IID_WHITEPLAYER, x, y, 0);
						m_gameStatus = "White's Turn";
					}
				}
				else
					m_gameStatus = "Pick another spot to place a piece";

				break;
		}
		
		// If pieces of one team surround anonothers delete the surrounded ones

		capture(m_pieces);


		return GWSTATUS_CONTINUE_GAME;
		
	}


	virtual void cleanUp()
	{
		
		for (int y = 0; y < VIEW_HEIGHT; y++)        
			for (int x = 0; x < VIEW_WIDTH; x++)
			{
				if (m_actorlist[y][x] != nullptr)
				{
					delete m_actorlist[y][x];
					m_actorlist[y][x] = nullptr;
				}
				/*
				if (m_pieceposition[y][x] != nullptr)
				{
					delete m_pieceposition[y][x];
					m_pieceposition[y][x] = nullptr;
				}
				*/
			}
		while (m_pieces.size() != 0)
		{
			delete m_pieces.back();
			m_pieces.pop_back();
		}
		
		if (m_player != nullptr)
		{
			delete m_player;
			m_player = nullptr;
		}
		
	}


	int loadField();
	void capture(std::vector<Piece*> &pieces);
	//std::list<Actor*>& getActors(int x, int y); // returns reference to list

private:
	// 2D array for actor objects 
	Actor* m_actorlist[VIEW_HEIGHT][VIEW_WIDTH];
	Piece* m_pieceposition[VIEW_HEIGHT][VIEW_WIDTH];

	// Vector of all pieces placed on board
	std::vector<Piece*> m_pieces;
	Player* m_player;
	
	std::string m_gameStatus;
	int m_whiteScore;
	int m_blackScore;
};

#endif // STUDENTWORLD_H_
