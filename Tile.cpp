#include "pch.h"
#include "Tile.h"
#include "Game.h"
#include "SpriteComponent.h"


Tile::Tile(Game *game):
	Actor(game),
	mIsBlocked(false),
	mParent(nullptr),
	f(0.0f),
	g(0.0f),
	h(0.0f),
	mInOpenset(false),
	mInClosedSet(false)
{
	SetScale(1.06666f); 
	mSprite = new SpriteComponent(this);

}

void Tile::SetTextureForTile() 
{
	if (!mIsBlocked) 
	{
		mSprite->SetTexture(GetGame()->GetTexture("Assets/Tile.png")); 
	}
	else 
	{
		mSprite->SetTexture(GetGame()->GetTexture("Assets/BlockedTile.png")); 
	}
}


Tile::~Tile()
{
}
