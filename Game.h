#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include "Rat.h"
#include "Grid.h"
#include "Cheese.h"

class Game
{

public:
	Game();

	~Game();

	bool Initialize(); 
	void RunGame(); 
	void Shutdown();
	void LoadData(); 
	void UnloadData(); 

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor); 
	
	void AddSprite(class SpriteComponent *sprite); 
	void RemoveSprite(class SpriteComponent *sprite); 

	SDL_Texture* GetTexture(std::string filename); 

	//std::queue<class Cheese*>& GetCheeses() { return mCheeses;  }
	class Rat *GetRat() const { return mRat;  }
	class Cheese* GetCheese() const { return mCheese;  }
	class Grid *GetGrid() const { return mGrid;  }

private:

	void ProcessInput(); 
	void UpdateGame(); 
	void GenerateOutput(); 

	SDL_Renderer *mRenderer;
	SDL_Window *mWindow; 

	bool mIsRunning; 
	bool mIsUpdatingActors; 

	std::vector<class Actor* > mActors; 
	std::vector<class Actor* > mPendingActors; 
	
	std::vector<class SpriteComponent*> mSprites; 

	std::unordered_map<std::string, SDL_Texture*> mTextures;
	float mTicksCount; 

	class Rat* mRat; 
	class Cheese *mCheese; 
	//std::queue<class Cheese*> mCheeses; 
	class Grid *mGrid; 


};

bool procees(const class SpriteComponent* s1, const class SpriteComponent* s2); 

