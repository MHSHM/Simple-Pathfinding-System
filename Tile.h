#pragma once
#include "Actor.h"
class Tile : public Actor
{
public:
	friend class Grid; 
	Tile(class Game *game);
	~Tile();

	Tile *GetParent() const { return mParent;  }
	void IsBlocked(bool val) { mIsBlocked = val;  }
	float GetF() const { return f;  }

	void SetTextureForTile(); 

private:

	std::vector<Tile*> mAdjacent; 
	Tile *mParent; 
	float f; 
	float g; 
	float h; 
	bool mInOpenset; 
	bool mInClosedSet; 


	bool mIsBlocked; 
	class SpriteComponent *mSprite; 
};

