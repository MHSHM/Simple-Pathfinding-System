#include "pch.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"

SpriteComponent::SpriteComponent(Actor *actor , int drawOrder):
	Component(actor),
	drawOrder(drawOrder),
	mTextureWidth(0),
	mTextureHeight(0)
{
	mOwner->GetGame()->AddSprite(this); 
}

void SpriteComponent::Draw(SDL_Renderer *renderer) 
{
	if (mTexture) 
	{
		SDL_Rect r; 

		r.w = static_cast<int>(mOwner->GetScale() * mTextureWidth); 
		r.h = static_cast<int>(mOwner->GetScale() * mTextureHeight); 

		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2); 
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2); 
	
		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE); 
	}
}

void SpriteComponent::SetTexture(SDL_Texture *texture) 
{
	mTexture = texture; 
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight); 
}


SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this); 
}
