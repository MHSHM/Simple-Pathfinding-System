#pragma once
#include "Component.h"
#include "SDL_image.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor *actor , int drawOrder = 10);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer *renderer);
	virtual void SetTexture(SDL_Texture* texture); 

	int GetDrawOrder() const { return drawOrder;  }

private:

	int drawOrder; 
	SDL_Texture* mTexture; 

	int mTextureWidth; 
	int mTextureHeight; 
};

