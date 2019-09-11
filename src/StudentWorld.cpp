#include "StudentWorld.h"
#include <string>
#include <queue>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

int StudentWorld::loadField()
{
	// REMEBER NULL CHARACTER AT THE END: THAT IS WHY VIEW_WIDTH + 1
	// THE FIELD IS UPSIDE DOWN COMPARED TO WHAT IS ACTUALLY DISPLAYED AND ANIMATED
	char field[VIEW_HEIGHT][VIEW_WIDTH + 1] =
	{ 
		{"                   "},
		{"                   "},
	    {"  *      *      *  "},
		{"                   "},
		{"                   "},
		{"                   "},
		{"                   "},
		{"                   "},
		{"                   "},
		{"  *      P      *  "},
		{"                   "},
		{"                   "},
		{"                   "},
		{"                   "},
		{"                   "},
		{"                   "},
		{"  *      *      *  "},
		{"                   "},
		{"                   "}
	};
		

	for (int x = 0; x < VIEW_WIDTH; x++)        // adding stuff to the list from the field
		for (int y = 0; y < VIEW_HEIGHT; y++)
		{

			// read the field  ad create new objects based on items on the field
			char item = field[x][y];
			
			if (item == 'P')
			{
				Player* ptr = new Player(this, IID_BLACKPLAYER, y, x, 1);
				m_player = ptr;
				
			}
			
			if (item == ' ')
			{
				Actor* ptr = new Board(this, IID_BOARD, y, x);
				m_actorlist[y][x] = ptr;
			} 
			else   // puts star at each point with * and at P
			{
				Actor* ptr = new Board(this, IID_STAR, y, x);
				m_actorlist[y][x] = ptr;
			}
			
		}
	return GWSTATUS_CONTINUE_GAME;
}

//When a pieces of the opposite team surrounds your pieces, your pieces are deleted or captured
void StudentWorld::capture(vector<Piece*> &pieces)
{
	for (int i = 0; i < pieces.size(); i++)
	{
		queue<Piece*> pieceQueue;
		vector<Piece*> capturedPieces;
		pieceQueue.push(pieces[i]);
		Piece* ptr = pieceQueue.front();
		bool safe = false;

		if (ptr != nullptr && !ptr->isMarked() && !ptr->isSafe())
		{
			while (!pieceQueue.empty())
			{
				ptr = pieceQueue.front();


				ptr->mark();
				capturedPieces.push_back(ptr);
				pieceQueue.pop();

				// NORTH
			
				if (ptr->getY() + 1 < VIEW_HEIGHT && m_pieceposition[ptr->getY() + 1][ptr->getX()] == nullptr)
				{
					safe = true;
				}

				// SOUTH
				
				if (ptr->getY() - 1 >= 0 && m_pieceposition[ptr->getY() - 1][ptr->getX()] == nullptr)
				{
					safe = true;
				}

				// EAST
				
				if (ptr->getX() + 1 < VIEW_WIDTH && m_pieceposition[ptr->getY()][ptr->getX() + 1] == nullptr)
				{
					safe = true;
				}

				// WEST
			
				if (ptr->getX() - 1 >= 0 && m_pieceposition[ptr->getY()][ptr->getX() - 1] == nullptr)
				{
					safe = true;
				}





				// NORTH
				if (ptr->getY() + 1 < VIEW_HEIGHT && m_pieceposition[ptr->getY() + 1][ptr->getX()] != nullptr)
				{
					if (ptr->team() == m_pieceposition[ptr->getY() + 1][ptr->getX()]->team() && !m_pieceposition[ptr->getY() + 1][ptr->getX()]->isMarked())
					{
						pieceQueue.push(m_pieceposition[ptr->getY() + 1][ptr->getX()]);
						m_pieceposition[ptr->getY() + 1][ptr->getX()]->mark();
					}
				}

				// SOUTH
				if (ptr->getY() - 1 >= 0 && m_pieceposition[ptr->getY() - 1][ptr->getX()] != nullptr)
				{
					if (ptr->team() == m_pieceposition[ptr->getY() - 1][ptr->getX()]->team() && !m_pieceposition[ptr->getY() - 1][ptr->getX()]->isMarked())
					{
						pieceQueue.push(m_pieceposition[ptr->getY() - 1][ptr->getX()]);
						m_pieceposition[ptr->getY() - 1][ptr->getX()]->mark();
					}
				}
			

				// EAST
				if (ptr->getX() + 1 < VIEW_WIDTH && m_pieceposition[ptr->getY()][ptr->getX() + 1] != nullptr)
				{
					if (ptr->team() == m_pieceposition[ptr->getY()][ptr->getX() + 1]->team() && !m_pieceposition[ptr->getY()][ptr->getX() + 1]->isMarked())
					{
						pieceQueue.push(m_pieceposition[ptr->getY()][ptr->getX() + 1]);
						m_pieceposition[ptr->getY()][ptr->getX() + 1]->mark();
					}
					
				}

				// WEST
				if (ptr->getX() - 1 >= 0 && m_pieceposition[ptr->getY()][ptr->getX() - 1] != nullptr)
				{
					if (ptr->team() == m_pieceposition[ptr->getY()][ptr->getX() - 1]->team() && !m_pieceposition[ptr->getY()][ptr->getX() - 1]->isMarked())
					{
						pieceQueue.push(m_pieceposition[ptr->getY()][ptr->getX() - 1]);
						m_pieceposition[ptr->getY()][ptr->getX() - 1]->mark();
					}
				}

				
			}

			if (pieceQueue.empty() && safe == false)
			{
				// delete surrounded 

				// add score of territory claimed
				if (capturedPieces.at(0)->team() == 0)
				{
					m_blackScore += capturedPieces.size();
				}
				else if (capturedPieces.at(0)->team() == 1)
				{
					m_whiteScore += capturedPieces.size();
				}

				for (int i = 0; i < capturedPieces.size(); i++)
				{
					for (int j = 0; j < m_pieces.size(); j++)
					{
						if (m_pieces[j] != nullptr)
						{
							if (capturedPieces[i]->getY() == m_pieces[j]->getY() && capturedPieces[i]->getX() == m_pieces[j]->getX())
							{
								m_pieces[j] = nullptr;
								pieces[j] = nullptr;
								//m_pieces.erase(m_pieces.begin() + j);
								//pieces.erase(m_pieces.begin() + j);
							}
						}
					}

					m_pieceposition[capturedPieces[i]->getY()][capturedPieces[i]->getX()] = nullptr; // need to set as nullptr to avoid double deletes and crash
					delete capturedPieces[i];
				}
			}
		}
	}

	for (int i = 0; i < pieces.size(); i++)
	{
		if (pieces[i] != nullptr)
		{
			pieces[i]->notSafe();
			pieces[i]->unMark();
		}
	}
}

/*
list<Actor*>& StudentWorld::getActors(int x, int y) 
{
	return m_actorlist[y][x];
}
*/
