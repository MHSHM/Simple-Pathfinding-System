#include "pch.h"
#include "Cheese.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <stdlib.h>
#include <time.h>

Cheese::Cheese(Game *game):
	Actor(game)
{ 
	SetScale(2.0f); 
	SetPosition(GetGame()->GetGrid()->GetEnd()->GetPosition()); 

	SpriteComponent *sprite = new SpriteComponent(this); 
	sprite->SetTexture(GetGame()->GetTexture("Assets/Cheese.png")); 

	mCircle = new CircleComponent(this); 
	mCircle->SetRadius(10.0f); 
}


Cheese::~Cheese()
{
}
