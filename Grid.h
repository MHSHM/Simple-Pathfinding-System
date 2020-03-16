#pragma once
#include "Actor.h"
class Grid : public Actor
{
public:
	Grid(class Game *game);
	~Grid();

	bool FindPath(class Tile *start , class Tile *goal);
	bool IsPathFound() { return mPathFound;  }
	

	class Tile* GetStart(); 
	class Tile* GetEnd(); 
	std::vector< std::vector<class Tile*> > GetTiles() { return mTiles; }
	
	bool ValidCell(int x, int y) { return x >= 0 && x < rows && y >= 0 && y < columns;  }

private:
	std::vector< std::vector<class Tile*> > mTiles;

	int rows; 
	int columns; 

	bool mPathFound; 

	int cellSize; 

	int dx[4] = { 1,-1,0,0 };
	int dy[4] = { 0,0,1,-1 };
	//int dx[8] = { 1,-1,0,0,-1,1,1,-1 };
	//int dy[8] = { 0,0,1,-1,-1,-1,1,1 };
};
