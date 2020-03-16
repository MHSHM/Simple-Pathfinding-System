#include "pch.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include <algorithm>
#include <string>
#include "Tile.h"


Game::Game() :
	mWindow(nullptr),
	mRenderer(nullptr),
	mIsRunning(true),
	mIsUpdatingActors(false)
{
}

bool Game::Initialize() 
{
	int init = SDL_Init(SDL_INIT_VIDEO);
	if (init != 0) 
	{
		SDL_Log(SDL_GetError());
		return 0;
	}

	mWindow = SDL_CreateWindow("Pathfinding" , 100 , 100 , 1024 , 768 , 0); 
	if (mWindow == nullptr) 
	{
		SDL_Log(SDL_GetError());
		return 0; 
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		SDL_Log(SDL_GetError());
		return 0; 
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		return 0;
	}

	mTicksCount = SDL_GetTicks(); 
	LoadData(); 
	return true; 
}

void Game::ProcessInput() 
{
	SDL_Event e; 
	while (SDL_PollEvent(&e)) 
	{
		switch (e.type)
		{
			case SDL_QUIT:
				mIsRunning = false; 
				break; 
		}
	}
}

void Game::UpdateGame() 
{
	float deltaTime = SDL_GetTicks() - mTicksCount;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	mIsUpdatingActors = true; 
	for (auto actor : mActors) 
	{
		actor->Update(deltaTime); 
	}
	mIsUpdatingActors = false;

	for (auto pendingActor : mPendingActors) 
	{
		mActors.emplace_back(pendingActor); 
	}

	std::vector<Actor*> deadActors; 

	for (auto actor : mActors) 
	{
		if (!actor->IsActive()) 
		{
			delete actor; 
		}
	}
}

void Game::GenerateOutput() 
{
	SDL_SetRenderDrawColor(mRenderer , 255 , 255 , 255 , 1);
	SDL_RenderClear(mRenderer); 

	for (auto sprite : mSprites) 
	{
		sprite->Draw(mRenderer); 
	}

	SDL_RenderPresent(mRenderer);
}

void Game::RunGame() 
{
	// game loop
	while (mIsRunning) 
	{
		ProcessInput(); 
		UpdateGame(); 
		GenerateOutput(); 
	}
}

void Game::AddActor(Actor *actor) 
{
	if (mIsUpdatingActors) 
	{
		mPendingActors.emplace_back(actor); 
	}
	else 
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor *actor) 
{
	auto iter = std::find(mActors.begin(), mActors.end() , actor);
	if (iter != mActors.end()) 
	{
		mActors.erase(iter);
	}

}

void Game::AddSprite(SpriteComponent* sprite) 
{
	mSprites.emplace_back(sprite); 
	std::sort(mSprites.begin(), mSprites.end(), proceed); 
}

void Game::RemoveSprite(SpriteComponent* sprite) 
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite); 
	if (iter != mSprites.end()) 
	{
		mSprites.erase(iter); 
	}
}

SDL_Texture* Game::GetTexture(std::string filename) 
{
	SDL_Texture* texture = nullptr; 
	auto it = mTextures.find(filename); 
	if (it != mTextures.end()) 
	{
		texture = it->second; 
	}
	else 
	{
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log(SDL_GetError());
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(mRenderer, surf);
		if (texture == nullptr)
		{
			SDL_Log(SDL_GetError());
			return nullptr;
		}
		SDL_FreeSurface(surf);
		mTextures.emplace(filename.c_str(), texture);
	} 
	return texture; 
}

bool procees(const SpriteComponent* s1, const SpriteComponent* s2) 
{
	return s1->GetDrawOrder() < s2->GetDrawOrder(); 
}

void Game::LoadData() 
{
	mGrid = new Grid(this); 
	mCheese = new Cheese(this);
	mRat = new Rat(this); 
}


void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}


void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}



Game::~Game()
{
}
