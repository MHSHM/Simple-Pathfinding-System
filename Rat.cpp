#include "pch.h"
#include "Rat.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include "Cheese.h"
#include <stdlib.h>
#include <time.h>
#include <queue>

Rat::Rat(Game *game) :
	mIsPathFound(false),
	Actor(game)
{ 
	Vector2 pos = GetGame()->GetGrid()->GetStart()->GetPosition(); 
	
	SetPosition(pos);
	SetRotation(0.0f); 
	SetScale(0.12f); 

	SpriteComponent *spt = new SpriteComponent(this); 
	SDL_Texture *texture = game->GetTexture("Assets/Rat.png");
	spt->SetTexture(texture); 

	mCircle = new CircleComponent(this); 
	mCircle->SetRadius(20.0f); 

	nav = new NavComponent(this); 
	nav->SetForwardSpeed(50.0f);

	//get path
	mIsPathFound = GetGame()->GetGrid()->FindPath(GetGame()->GetGrid()->GetEnd(), GetGame()->GetGrid()->GetStart()); 
	if (mIsPathFound) 
	{
		nav->StartPath(GetGame()->GetGrid()->GetStart()); 
	}
}

void Rat::UpdateActor(float deltaTime) 
{
	// if the rat collides with the cheese
	if (Intersect(mCircle , GetGame()->GetCheese()->GetCircle())) 
	{
		//destroy cheese
		GetGame()->GetCheese()->SetActive(false); 

		//pause rat
		SetPaused(true); 
	}
}

Rat::~Rat()
{
}

bool Intersect(CircleComponent* c1, CircleComponent* c2) 
{
	Vector2 diff = c1->GetCenter() - c2->GetCenter();
	float lengthSqrd = diff.LengthSq();
	float radiusSumSqurd = c1->GetRadius() + c2->GetRadius();
	radiusSumSqurd *= radiusSumSqurd;
	return lengthSqrd < radiusSumSqurd;
}