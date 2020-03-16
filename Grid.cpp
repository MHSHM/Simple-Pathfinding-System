#include "pch.h"
#include "Grid.h"
#include "Tile.h"
#include "Game.h"
#include <algorithm>
#include <time.h>
#include <stdlib.h>

Grid::Grid(Game *game):
	Actor(game),
	rows(12),
	columns(16),
	cellSize(64),
	mPathFound(false)
{
	// resize vector to make it 2D Grid
	mTiles.resize(rows); 
	for (int i = 0; i < (int)mTiles.size(); ++i) 
	{
		mTiles[i].resize(columns); 
	}

	//initialize grid
	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < columns; ++j)
		{
			mTiles[i][j] = new Tile(GetGame());			
			mTiles[i][j]->SetTextureForTile();

			Vector2 pos; 
			pos.x = (cellSize / 2.0f) + (j * cellSize);
			pos.y = cellSize/2.0f + (i * cellSize); 
			mTiles[i][j]->SetPosition(pos);
		}
	}

	// generate random blocked cells
	int i = 0;
	srand((time_t)time(NULL)); 
	while (i < 50) 
	{
		int x = rand() % 11; 
		int y = rand() % 15;
		
		// make sure that rat and cheese won't be blocked cells
		if (x == 0 && y == 0 || x == 8 && y == 15) 
		{
			continue; 
		}

		mTiles[x][y]->mIsBlocked = true; 
		mTiles[x][y]->SetTextureForTile(); 
		++i; 
	}


	// set adjacent list for each cell

	for (int i = 0; i < rows; ++i) 
	{
		for (int j = 0; j < columns; ++j) 
		{
			for (int k = 0; k < 8; ++k) 
			{
				int newI = i + dx[k]; 
				int newJ = j + dy[k]; 
				if (ValidCell(newI , newJ)) 
				{
					mTiles[i][j]->mAdjacent.emplace_back(mTiles[newI][newJ]); 
				}
			}
		}
	}
}

bool Grid::FindPath(Tile* start , Tile* goal) 
{
	// find shortest path using A*

	std::vector<Tile*> openSet; 
	Tile* current = start; 
	start->mInClosedSet = true;

	do 
	{
	
		for (Tile* adj : current->mAdjacent) 
		{
			if (adj->mIsBlocked) 
			{
				continue; 
			}

			if (!adj->mInClosedSet) 
			{
				if (!adj->mInOpenset) 
				{
					adj->mParent = current; 
					adj->g = current->g + 1 ; 
					adj->h = (adj->GetPosition() - goal->GetPosition()).Length() ; 
					adj->f = adj->h + adj->g;
					adj->mInOpenset = true; 
					openSet.emplace_back(adj); 
				}
				else 
				{
					float newG = current->g + 1;
					if (newG < adj->g) 
					{
						adj->mParent = current; 
						adj->g = newG;
						adj->f = adj->g + adj->h;
					}
				}
			}
		}

		if (openSet.empty()) 
		{
			break; 
		}

		auto iter = std::min_element(openSet.begin(), openSet.end(), [](Tile* a, Tile* b) {
			return a->f < b->f;
		});
		current = *iter; 
		current->mInClosedSet = true; 
		current->mInOpenset = false; 
		openSet.erase(iter); 

	} while (current != goal);

	return (current == goal) ? true : false;
}

Tile* Grid::GetStart() 
{
	return mTiles[0][0]; 
}

Tile* Grid::GetEnd() 
{
	return mTiles[9][15];
}

Grid::~Grid()
{
}
